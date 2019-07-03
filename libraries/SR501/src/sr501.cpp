
#include "sr501.h"

SR501::SR501()
{
    setPin(0*32+6);
    
    exportGPIO();
    usleep(25000);
    
    setDirection(1);
}

SR501::SR501(int pin)
{
    setPin(pin);
    
    exportGPIO();
    usleep(25000);
    
    setDirection(1);
}

SR501::~SR501(void)
{
    unexportGPIO();
}

int SR501::getSignal(void)
{
    return getValue();
}
