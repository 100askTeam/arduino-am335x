#ifndef _RTC_H
#define _RTC_H

#include <Arduino.h>
#include "i2c.h"

#define H12 1
#define H24 0
#define AM  1
#define PM  0

typedef struct {
    unsigned int year;
    unsigned char month;
    unsigned char day;
    unsigned char week; //0~6
    unsigned char hour;
    unsigned char minute;
    unsigned char second;   
}Time;

class RTC : public I2C {
    private: 
        unsigned int year;
        unsigned char month;
        unsigned char day;
        unsigned char week; //0~6
        unsigned char hour;
        unsigned char minute;
        unsigned char second;

        const char *week_string[7] = {"Sun","Mon","Tue","Wed","Thur", "Fri","Sat"};
        
        virtual void rx8025Init(void);

    public:
        RTC(int num);
        virtual Time readTime(void);
        virtual int setTime(Time t);
        virtual void timePrintf(void);
        virtual ~RTC();
};

    
#endif