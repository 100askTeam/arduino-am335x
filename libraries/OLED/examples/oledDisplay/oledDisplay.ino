/* 
* Filename:    oledDisplay.ino
* Revision:    1.0
* Date:        2019/06/03
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    OLED display.
* Notes:       none.
* Description: 
* 1. 实例化OLED，传入参数为对应的SPI接口编号；
* 2. page为OLED显示高度，总共为8，每行字符占据两行；
* 3. 使用OLEDPrint显示数据，参数为：行位置、列位置、数据内容；
* 4. 如果page小于8，显示数据，超过8则清空显示；
*/
#include <Arduino.h>
#include <oled.h>

int main(int argc, char **argv)
{
    OLED oled(1);
    int page = 0;

    while(1)
    {
        if(page < 8)
        {
            oled.OLEDPrint(page, 0, "1234567890123456"); 
            page += 2;
            sleep(1);   
        }
        else
        {
            page = 0;
            oled.OLEDClearAll();    
            sleep(1);
        }   
    }
}
