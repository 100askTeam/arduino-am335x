
#include "rtc.h"

RTC::RTC(int num)
{
    if (num == 1)
        I2C(I2C0, RX8025SA);
    else if(num == 2)
        I2C(I2C1, RX8025SA);
    
    this->m_iDevAddr = RX8025SA; 
    
    this->rx8025Init();
}


void RTC::rx8025Init(void)
{
    Time t;
    unsigned char read_buf[2], write_buf = 0;
    int need_reset=0, need_clear=0;
    readRegister((0x0E<<4)|0x08, 2, read_buf);

    if (read_buf[1] & (1<<4)) 
    {
        printf("power-on reset was detected, you may have to readjust the clock\n");
        need_reset = 1;
    }
    
    if (read_buf[1] & (1<<6)) 
    {
        printf("a power voltage drop was detected, you may have to readjust the clock\n");
        need_reset = 1;
    }
    
    if (!(read_buf[1] & (1<<5))) 
    {
        printf("Oscillation stop was detected, you may have to readjust the clock\n");
        need_reset = 1;
    }
    
    if (read_buf[1] & ((1<<1) | (1<<0))) 
    {
        //printf("Alarm was detected\n");
        need_clear = 1;
    }
    
    if (!(read_buf[1] & (1<<2))) 
        need_clear = 1;
    
    
    if (need_reset || need_clear)
    {
        write_buf = read_buf[0];
        write_buf &= ~((1<<4)|(1<<6)|(1<<2)|(1<<1)|(1<<0));
        write_buf |= (1<<5);
        writeRegister(0x0F<<4, write_buf);
    }
    
    if (!(read_buf[0] & (1<<6))) //改为24小时制
    {
        write_buf = read_buf[0];
        write_buf |= (1<<5);
        writeRegister(0x0F<<4, write_buf);
        
        readRegister((0x0E<<4)|0x08, 1, read_buf);
        printf("reg=0x%x\n", read_buf[0]);
    }
    else
    {
        readRegister((0x0E<<4)|0x08, 1, read_buf);
        printf("reg=0x%x\n", read_buf[0]);
    }
    
    if(need_reset)
    {
        //默认时间 2000/1/1
        t.year = 2000;
        t.month = 1;
        t.day = 1;
        t.week = 6;
        t.hour = 0;
        t.minute = 0;
        t.second = 0;

        this->setTime(t);
        printf("Set the default time:2000-01-01 00:00:00, you may have to readjust the clock\n");
    }
}


Time RTC::readTime()
{
    Time t;
    unsigned char rtc_data[7];

    readRegister((0x00<<4)|0x08, 7, rtc_data);
    
    printf("readTime: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n", 
    rtc_data[0], rtc_data[1], rtc_data[2], rtc_data[3], rtc_data[4], rtc_data[5], rtc_data[6]);
 
    this->second = (rtc_data[0] & 0xF) + ((rtc_data[0] & 0x70)>>4)*10;
    this->minute = (rtc_data[1] & 0xF) + ((rtc_data[1] & 0x70)>>4)*10;
#if 0  //12小时制  
    if (rtc_data[2] == 0x12)
        this->hour = 0;
    else if (rtc_data[2] <= 0x11 && rtc_data[2] >= 0x1)
        this->hour = (rtc_data[2] & 0xF) + ((rtc_data[2] & 0x10)>>4)*10;
    else if (rtc_data[2] == 0x32)
        this->hour = 12;
    else if (rtc_data[2] >= 21 && rtc_data[2] <= 0x31)
        this->hour = (rtc_data[2] & 0xF) + ((rtc_data[2] & 0x30)>>4)*10 -8;
#else  //24小时制  
    this->hour   = (rtc_data[2] & 0xF) + ((rtc_data[2] & 0x30)>>4)*10;
#endif
    this->week   = (rtc_data[3] & 0x7);
    this->day    = (rtc_data[4] & 0xF) + ((rtc_data[4] & 0x30)>>4)*10;
    this->month  = (rtc_data[5] & 0xF) + ((rtc_data[5] & 0x10)>>4)*10;
    this->year   = (rtc_data[6] & 0xF) + ((rtc_data[6] & 0xF0)>>4)*10 + 2000;

    t.second = this->second;
    t.minute = this->minute;
    t.hour   = this->hour;  
    t.week   = this->week;  
    t.day    = this->day;   
    t.month  = this->month; 
    t.year   = this->year;  
    
    return t;
}

int RTC::setTime(Time t)
{
    unsigned int ctrl;
    unsigned char rtc_data[7];
    memset(rtc_data, 0, 7*sizeof(unsigned char));
    
    this->second = t.second;
    this->minute = t.minute;
    this->hour   = t.hour;
    this->week   = t.week;
    this->day    = t.day;
    this->month  = t.month; 
    this->year   = t.year;  

    if(this->second > 59)
        goto err;
    else
        rtc_data[0] = (this->second/10)<<4 | (this->second%10);
    
    if(this->minute > 59)
        goto err;
    else
        rtc_data[1] = (this->minute/10)<<4 | (this->minute%10);
    

    if (this->hour>23)
        goto err;   
    else
    {
#if 0  //12小时制
        if (this->hour == 0)
            rtc_data[2] = 0x12;
        else if (this->hour <= 11 && this->hour >= 1)
            rtc_data[2] = (this->hour/10)<<4 | (this->hour%10);
        else if (this->hour == 12)
            rtc_data[2] = 0x32;
        else if (this->hour >= 13 && this->hour <= 23)
            rtc_data[2] = ((this->hour + 8)/10)<<4 | ((this->hour + 8)%10);
#else  //24小时制  
        rtc_data[2] = (this->hour/10)<<4 | (this->hour%10);  
#endif
    }
 
    if(this->week>6)
        goto err;
    else
        rtc_data[3] = this->week;
    
    
    if(this->day > 31)
        goto err;
    else
        rtc_data[4] = (this->day/10)<<4 | (this->day%10);
    
    
    if(this->month > 12 || this->month==0)
        goto err;
    else
        rtc_data[5] = (this->month/10)<<4 | (this->month%10);
    
    
    if((this->year-2000) > 99)
        goto err;
    else
        rtc_data[6] = ((this->year-2000)/10)<<4 | ((this->year-2000)%10);
    
    writeRegister((0x00<<4)|0x08, 7, rtc_data);
    
    
    
    ctrl = readRegister((0x0E<<4)|0x08);
    ctrl |=  (1<<6); 
    writeRegister(0x0E<<4, ctrl);
    
    //printf("ctrl=0x%08x\n", readRegister((0x0E<<4)|0x08));
    
    return 0;

err:
    printf("setTime err.\n\r");
    return -1;       

}

void RTC::timePrintf()
{
    readTime();

    printf("Time: %d-%02d-%02d %02d:%02d:%02d [%s]\n", this->year, this->month,this->day,this->hour,this->minute,this->second, this->week_string[this->week]);
}


RTC::~RTC()
{
    
}