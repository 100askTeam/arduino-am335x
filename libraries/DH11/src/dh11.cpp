
#include "dh11.h"

DH11::DH11()
{   
    this->m_iPin = (0*32+6);
    this->m_sPath = "/dev/dh11";
    
    this->m_iFile = open(this->m_sPath.c_str(), O_RDWR);
    if (this->m_iFile < 0)
        perror("can't open device");

    if(ioctl(this->m_iFile, DH11_IOCINIT, &this->m_iPin) < 0) 
        perror("DH11: Failed to init to the device\n");
    
    msleep(1500);
}

DH11::DH11(int pin)
{   
    this->m_iPin = pin;
    this->m_sPath = "/dev/dh11";
    
    this->m_iFile = open(this->m_sPath.c_str(), O_RDWR);
    if (this->m_iFile < 0)
        perror("can't open device");

    if(ioctl(this->m_iFile, DH11_IOCINIT, &this->m_iPin) < 0) 
        perror("DH11: Failed to init to the device\n");
    
    msleep(1500);
}

DH11::~DH11(void)
{
    close(this->m_iFile);
}

int DH11::readTemperature(void)
{
    struct dh11_value_msg msg;
    
    if(ioctl(this->m_iFile, DH11_IOCGVALUE, &msg) < 0) 
        perror("DH11: DH11_IOCGVALUE Failed\n");
    
    return msg.temperature;
}

int DH11::readHumdity(void)
{
    struct dh11_value_msg msg;
    
    if(ioctl(this->m_iFile, DH11_IOCGVALUE, &msg) < 0) 
        perror("DH11: DH11_IOCGVALUE Failed\n");
    
    return msg.humdity;
}


