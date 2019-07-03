/* 
* Filename:    turnOffLED.ino
* Revision:    1.0
* Date:        2019/05/31
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    turn Off LED4. 
* Notes:       none.
* Description: 
* 1. 实例化LED；
* 2. 实例KEYBOARD；
* 3. 调用readKey()读取按键状态；
* 4. 如果KEY4按下，或者长按，关闭LED4;
*/
#include <Arduino.h>
#include <led.h>
#include <keyboard.h>

int main(int argc, char **argv)
{
    LED led(LED4); 

    KEYBOARD keyboard;
    
    while(1)
    {
        keyboard.readKey();
        
        //如果KEY4按下，或者长按，关闭LED4
        if((keyboard.code == KEY4) && (keyboard.value == 1 || keyboard.value == 2)) 
            led.off();
        else
            led.on();
    }
}
