#ifndef _LED_H
#define _LED_H

#include "gpio.h"

#define LED1 (1*32+16)
#define LED2 (1*32+17)
#define LED3 (1*32+19)
#define LED4 (1*32+21)


class LED : public GPIO {
    public:

        LED(int pin);
        ~LED(void);
        
        int on(void);
        int off(void);
};


#endif 


