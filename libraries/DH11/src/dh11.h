#ifndef _DH11_H
#define _DH11_H

#include <Arduino.h>
#include <gpio.h>

#define DH11_IOC_MAGIC    'd'
#define DH11_IOCINIT      _IOW(DH11_IOC_MAGIC, 0, int)
#define DH11_IOCGVALUE    _IOWR(DH11_IOC_MAGIC, 2, void *)

struct dh11_value_msg {
    unsigned char humdity;
    unsigned char temperature;
};


class DH11  {
    private:
        int m_iPin;
        string m_sPath;
        int m_iFile;
    
    public:
        DH11();
        DH11(int pin);
        
        virtual int readTemperature(void);
        virtual int readHumdity(void);
        
        ~DH11(void);
};


#endif


