/* 
* Filename:    readData.ino
* Revision:    1.0
* Date:        2019/06/03
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Read ADXL345 data.
* Notes:       none.
* Description: 
* 1. 实例化ADXL345，传入参数为对应的SPI接口编号；
* 2. 在循环里，调用readData()获取数据；
* 3. 打印x_value、y_value、z_value的值，其中setw用于格式化输出，使数据占据四个字符位置；
*/
#include <Arduino.h>
#include <adxl345.h>

int main(int argc, char **argv)
{
    ADXL345 adxl345(1);

    while(1)
    {
        adxl345.readData();
          
        cout << "X: " << setw(4) << adxl345.x_value 
          <<  "  Y: " << setw(4) << adxl345.y_value 
          <<  "  Z: " << setw(4) << adxl345.z_value << endl;

        msleep(200);    
    }
}
