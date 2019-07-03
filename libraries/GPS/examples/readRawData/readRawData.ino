/* 
* Filename:    readRawData.ino
* Revision:    1.0
* Date:        2019/06/03
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Get GPS raw data.
* Notes:       Only uart2 is supported for am335x.
* Description: 
* 1. 实例化GPS，传入参数为对应的UART接口编号；
* 2. 循环里，先清空RawData数据；
* 3. 使用readRawData()获取GPS原始数据，保存在RawData里；
* 4. 打印输出原始数据；
*/
#include <Arduino.h>
#include <gps.h>

int main(int argc, char **argv)
{
    GPS gps(2);
    
    while(1)
    {
        memset(gps.RawData,0,sizeof(gps.RawData));
        
        if(gps.readRawData(gps.RawData))
            cout << gps.RawData << endl;    
    }   
}
