/* 
* Filename:    readDH11.ino
* Revision:    1.0
* Date:        2019/05/31
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Read DH11 temperature and humidity values. 
* Notes:       none.
* Description: 
* 1. 实例化DH11，可指定所接GPIO，默认GPIO0；
* 2. 调用readTemperaturey()读取当前环境温度，并打印；
* 3. 调用readHumdity()读取当前环境湿度，并打印；
* 4. 读取间隔需1S以上；
*/
#include <Arduino.h>
#include <dh11.h>

int main(int argc, char **argv)
{
    DH11 dh11(GPIO0);

    while(1)
    {
        cout << "Temperature: " << dh11.readTemperature() << "'C" << endl;
        cout << "Humdity: " << dh11.readHumdity() << "%" << endl;

        sleep(1);
    }
}

