/* 
* Filename:    readWriteArray.ino
* Revision:    1.0
* Date:        2019/06/03
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Read and write array form EEPROM.
* Notes:       none.
* Description: 
* 1. 定义发送/接收数组，并设置待发送数据；
* 2. 计算发送/接收数组的长度；
* 3. 实例化EEPROM，传入参数为对应的I2C接口编号；
* 4. 调用writeEEPROM写EEPROM，参数为：待写起始地址、待写长度、待写数据；
* 5. 调用readEEPROM读EEPROM，参数为：待读起始地址、待读长度、待保存位置；
* 6. 循环打印接收的数据，观察是否和写的数据一致；
*/
#include <Arduino.h>
#include <eeprom.h>

int main(int argc, char **argv)
{
    int i;
    int txArray[5] = {10, 20, 30, 254, 255};
    int rxArray[5];
    int txLen = sizeof(txArray)/sizeof(txArray[0]);
    int rxLen = sizeof(rxArray)/sizeof(rxArray[0]);
    
    EEPROM eeprom(1);
    
    eeprom.writeEEPROM(0, txLen, txArray);
    eeprom.readEEPROM(0, rxLen, rxArray);
    
    cout << "rxArray: "; 
    for (i=0; i<rxLen; i++)
        cout << rxArray[i] << " " ; 
    cout << endl; 
}
