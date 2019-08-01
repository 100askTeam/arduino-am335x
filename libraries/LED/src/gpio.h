#ifndef GPIO_H
#define GPIO_H

#include <Arduino.h>

#define GPIO0 (0*32+6)
#define GPIO1 (0*32+7)
#define GPIO2 (0*32+12)
#define GPIO3 (1*32+20)
#define GPIO4 (1*32+18)

class GPIO {
    private:
        int m_iPin;
        string m_sPath;
        
    public:
        GPIO(void);
        GPIO(int pin);
        
        void setPin(int pin);
        int getPin(void);   
        
        void setPath(int pin);
        string getPath(void);
        
        int setDirection(int dir);
        int getDirection(void);
        
        int setValue(int val);
        int getValue(void);
        
        int exportGPIO(void);
        int unexportGPIO(void);
};

#endif