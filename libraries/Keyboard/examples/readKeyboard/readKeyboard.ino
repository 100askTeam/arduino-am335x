/* 
* Filename:    readKeyboard.ino
* Revision:    1.0
* Date:        2019/05/31
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Get Keyboard value. 
* Notes:       none.
* Description: 
* 1. 实例化KEYBOARD；
* 2. 循环里，调用readKey()读取按键状态；
* 3. 打印按键编号(code)和按键值(value)：
* 4. 按键编号对应如下：
*    KEY1 105
*    KEY2 106
*    KEY3 28
*    KEY4 1 
* 5. 按键值含义如下：
*    松开按键 0
*    按下按键 1
*    长按按键 2
*/
#include <Arduino.h>
#include <keyboard.h>

int main(int argc, char **argv)
{
    KEYBOARD keyboard;
    
    while(1)
    {
        keyboard.readKey();
        
        cout << "Code:" << keyboard.code << " Value:" << keyboard.value << endl;
    }
}

