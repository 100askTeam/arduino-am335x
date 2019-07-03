/* 
* Filename:    readWriteString.ino
* Revision:    1.0
* Date:        2019/06/03
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Read and write string form EEPROM.
* Notes:       none.
* Description: 
* 1. 定义发送/接收字符串，并设置待发送数据；
* 2. 实例化EEPROM，传入参数为对应的I2C接口编号；
* 3. 调用writeEEPROM写EEPROM，参数为：待写起始地址、待写字符串长度、待写数据；
* 4. 调用readEEPROM读EEPROM，参数为：待读起始地址、待读字符串长度、待保存位置；
* 5. 打印接收的数据，观察是否和写的数据一致；  
*/
#include <Arduino.h>
#include <eeprom.h>

int main(int argc, char **argv)
{
    string txString = "www.100ask.org";
    string rxString;

    EEPROM eeprom(1);

    eeprom.writeEEPROM(0, txString.size(), txString);
    eeprom.readEEPROM(0, txString.size(), &rxString);
    cout << "rxString: " << rxString << endl;
}
