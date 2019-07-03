#ifndef _GPS_H
#define _GPS_H


#include <Arduino.h>
#include "uart.h"

class GPS : public UART {
    private:

    public:
        char RawData[256];
    
        GPS(int num);
        ~GPS();
        virtual int readRawData(char *data);
        virtual int printfAnalyzeData();

};

    
#endif