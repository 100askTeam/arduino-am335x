
#include "rtc.h"

RTC::RTC(int num)
{
    if (num == 1)
        I2C(I2C0, RX8025SA);
    else if(num == 2)
        I2C(I2C1, RX8025SA);
    
    this->m_iDevAddr = RX8025SA; //bug
    
    this->rx8025Init();
}


void RTC::rx8025Init(void)
{
    unsigned char read_buf[2], write_buf=0;
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
    
    if(need_reset)
    {
        //默认时间 2000/1/1
        this->year = 2000;
        this->month = 1;
        this->day = 1;
        this->week = 6;
        this->hour = 0;
        this->minute = 0;
        this->second = 0;

        this->setTime();
        printf("Set the default time:2000-01-01 00:00:00, you may have to readjust the clock\n");
    }
}


int RTC::readTime()
{
    unsigned char rtc_data[7];

    readRegister((0x00<<4)|0x08, 7, rtc_data);
    
    //printf("readTime: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n", 
    //rtc_data[0], rtc_data[1], rtc_data[2], rtc_data[3], rtc_data[4], rtc_data[5], rtc_data[6]);
    
    this->second = (rtc_data[0] & 0xF) + ((rtc_data[0] & 0x70)>>4)*10;
    this->minute = (rtc_data[1] & 0xF) + ((rtc_data[1] & 0x70)>>4)*10;

    this->hour = (rtc_data[2] & 0xF) + ((rtc_data[2] & 0x30)>>4)*10;
    
    
    this->week   = (rtc_data[3] & 0x7);
    this->day    = (rtc_data[4] & 0xF) + ((rtc_data[4] & 0x30)>>4)*10;
    this->month  = (rtc_data[5] & 0xF) + ((rtc_data[5] & 0x10)>>4)*10;
    this->year   = (rtc_data[6] & 0xF) + ((rtc_data[6] & 0xF0)>>4)*10 + 2000;

    return 0;
}

int RTC::setTime()
{
    unsigned int ctrl;
    unsigned char rtc_data[7];
    memset(rtc_data, 0, 7*sizeof(unsigned char));

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
        rtc_data[2] = (this->hour/10)<<4 | (this->hour%10);     
    
        
    
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
    return 1;       

}

int RTC::timePrintf()
{
    readTime();

    printf("Time: %d-%02d-%02d %02d:%02d:%02d [%s]\n", this->year, this->month,this->day,this->hour,this->minute,this->second, this->week_string[this->week]);
    
    return 0;
}


RTC::~RTC()
{
    
}