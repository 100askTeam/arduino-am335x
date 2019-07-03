/* 
* Filename:    turnOnLED.ino
* Revision:    1.0
* Date:        2019/05/31
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    turn On LED4. 
* Notes:       none.
* Description: 
* 1. 实例化LED,并先关闭；
* 2. 实例IRDA；
* 3. 调用readKey()读取按键状态；
* 4. 如果KEY_1按下，或者长按，打开LED4;
*/
#include <Arduino.h>
#include <led.h>
#include <irda.h>


int main(int argc, char **argv)
{
    LED led(LED4); 
    led.off();

    IRDA irda(GPIO0);
    
    while(1)
    {
        irda.readKey();
        
        //如果KEY_1按下，或者长按，打开LED4
        if((irda.code == KEY_1) && (irda.value == 1 || irda.value == 2)) 
            led.on();
        else
            led.off();
    }
}
