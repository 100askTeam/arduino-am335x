/* 
* Filename:    readIRDA.ino
* Revision:    1.0
* Date:        2019/05/31
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Get IrDA value. 
* Notes:       none.
* Description: 
* 1. 实例化IRDA；
* 2. 调用readKey()读取按键，并判断返回值；
* 3. 调用getCode()获取按键编号code，调用getValue()获取按键值value，并打印：
* 4. 按键编号对应如下：
*    KEY_CHANNELDOWN        0x45
*    KEY_CHANNEL            0x46
*    KEY_CHANNELUP          0x47
*    KEY_PREVIOUS           0x44
*    KEY_NEXT               0x40
*    KEY_PLAYPAUSE          0x43
*    KEY_VOLUMEDOWN         0x07
*    KEY_VOLUMEUP           0x15
*    KEY_EQUAL              0x09                    
*    KEY_0                  0x16
*    KEY_F1                 0x19
*    KEY_F2                 0x0d                      
*    KEY_1                  0x0c
*    KEY_2                  0x18
*    KEY_3                  0x5e
*    KEY_4                  0x08
*    KEY_5                  0x1c
*    KEY_6                  0x5a
*    KEY_7                  0x42
*    KEY_8                  0x52
*    KEY_9                  0x4a

* 5. 按键值含义如下：
*    松开按键 0
*    按下按键 1
*    长按按键 2
*/
#include <Arduino.h>
#include <irda.h>

int main(int argc, char **argv)
{
    int ret;
    IRDA irda(GPIO0);
    
    while(1)
    {
        ret = irda.readKey();
        
        if(ret == 0)
            cout << "Code:" << irda.getCode() << " Value:" << irda.getValue() << endl;
    }
    
    return 0;
}

