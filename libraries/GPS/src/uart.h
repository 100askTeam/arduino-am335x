#ifndef _UART_H
#define _UART_H

#include <Arduino.h>

#define UART0_PATH  "/dev/ttyO0"
#define UART1_PATH  "/dev/ttyO1"
#define UART2_PATH  "/dev/ttyO2"
#define UART3_PATH  "/dev/ttyO3"

#define UART_A  2

class UART {
    private:
        string m_sPath;
        int m_iFile;
        //设置串口参数
        
    public:
        UART();
        UART(int num);
        ~UART(void);
        
        int setUART(void);
        
        int sendData(char *data, int len);
        int reviceData(char *data, int len);
};

#endif 


