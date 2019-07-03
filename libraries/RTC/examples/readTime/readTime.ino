/* 
* Filename:    readTime.ino
* Revision:    1.0
* Date:        2019/06/03
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Read Real Time Clock.
* Notes:       Onboard RTC at I2C0.
* Description: 
* 1. 实例化RTC，传入参数为对应的I2C接口编号；
* 2. 循环里，间隔1S,使用timePrintf()打印RTC模块时间；
* 3. 如果第一次上电，默认设置时间为2000-01-01 00:00:00 
*/
#include <Arduino.h>
#include <rtc.h>

int main(int argc, char **argv)
{
    RTC rtc(1);
    
    while(1)
    {
        rtc.timePrintf();
        sleep(1);
    } 
}
