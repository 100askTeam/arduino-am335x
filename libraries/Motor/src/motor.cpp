
#include "motor.h"

MOTOR::MOTOR()
{
    this->m_iPin1 = 6;
    this->m_iPin2 = 7;
    this->m_iPin3 = 12;
    this->m_iPin4 = 52;

    this->m_iSpeed = 4*2; 

    setPin(this->m_iPin1);
    exportGPIO();
    usleep(25000);
    setDirection(0); 
    setValue(0);

    setPin(this->m_iPin2);
    exportGPIO();
    usleep(25000);
    setDirection(0); 
    setValue(0);
    
    setPin(this->m_iPin3);
    exportGPIO();
    usleep(25000);
    setDirection(0); 
    setValue(0);
    
    setPin(this->m_iPin4);
    exportGPIO();
    usleep(25000);
    setDirection(0); 
    setValue(0);
}

MOTOR::~MOTOR(void)
{
    setPin(this->m_iPin1);
    setValue(0);
    unexportGPIO();
    
    setPin(this->m_iPin2);
    setValue(0);
    unexportGPIO();
    
    setPin(this->m_iPin3);
    setValue(0);
    unexportGPIO();
    
    setPin(this->m_iPin4);
    setValue(0);
    unexportGPIO();
}

int MOTOR::motorForward(int angle)
{   
    int i = 0;
    for(i=0; i<angle; i++) 
    {

        setPin(this->m_iPin1);
        setValue(1);
        setPin(this->m_iPin2);
        setValue(1);
        setPin(this->m_iPin3);
        setValue(0);    
        setPin(this->m_iPin4);
        setValue(0);    
        msleep(this->m_iSpeed);
        
        setPin(this->m_iPin1);
        setValue(0);
        setPin(this->m_iPin2);
        setValue(1);
        setPin(this->m_iPin3);
        setValue(1);    
        setPin(this->m_iPin4);
        setValue(0);    
        msleep(this->m_iSpeed);
        
        setPin(this->m_iPin1);
        setValue(0);
        setPin(this->m_iPin2);
        setValue(0);
        setPin(this->m_iPin3);
        setValue(1);    
        setPin(this->m_iPin4);
        setValue(1);    
        msleep(this->m_iSpeed);
        
        setPin(this->m_iPin1);
        setValue(1);
        setPin(this->m_iPin2);
        setValue(0);
        setPin(this->m_iPin3);
        setValue(0);    
        setPin(this->m_iPin4);
        setValue(1);    
        msleep(this->m_iSpeed);


    }

    return 0;
}

int MOTOR::motorReverse(int angle)
{
    int i = 0;
    for(i=0; i<angle; i++) 
    {
        setPin(this->m_iPin1);
        setValue(1);
        setPin(this->m_iPin2);
        setValue(1);
        setPin(this->m_iPin3);
        setValue(0);    
        setPin(this->m_iPin4);
        setValue(0);    
        msleep(this->m_iSpeed);
        
        setPin(this->m_iPin1);
        setValue(1);
        setPin(this->m_iPin2);
        setValue(0);
        setPin(this->m_iPin3);
        setValue(0);    
        setPin(this->m_iPin4);
        setValue(1);    
        msleep(this->m_iSpeed);
        
        setPin(this->m_iPin1);
        setValue(0);
        setPin(this->m_iPin2);
        setValue(0);
        setPin(this->m_iPin3);
        setValue(1);    
        setPin(this->m_iPin4);
        setValue(1);    
        msleep(this->m_iSpeed);
        
        setPin(this->m_iPin1);
        setValue(0);
        setPin(this->m_iPin2);
        setValue(1);
        setPin(this->m_iPin3);
        setValue(1);    
        setPin(this->m_iPin4);
        setValue(0);    
        msleep(this->m_iSpeed);
    }
    
    return 0;
}


int MOTOR::motorStop(void)
{
    setPin(this->m_iPin1);
    setValue(0);
    setPin(this->m_iPin2);
    setValue(0);
    setPin(this->m_iPin3);
    setValue(0);    
    setPin(this->m_iPin4);
    setValue(0);    
    msleep(this->m_iSpeed);
    
    return 0;
}


int MOTOR::setSpeed(int speed)
{
    if (speed > 10)
        speed = 10;
    if (speed < 1)
        speed = 1;
    
    this->m_iSpeed = 4 * speed; //low
    
    return 0;
}

int MOTOR::getSpeed(void)
{
    return this->m_iSpeed/4;
}


