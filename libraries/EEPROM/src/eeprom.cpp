
#include "eeprom.h"

EEPROM::EEPROM(int num)
{
    if (num == 1)
        I2C(I2C0, AT24C256);
    else if(num == 2)
        I2C(I2C1, AT24C256);
    
    this->m_iDevAddr = AT24C256; //bug
}

int EEPROM::readEEPROM(unsigned int addr, unsigned int len, string *rxBuffer)
{
    unsigned int i;
    unsigned char data[len];

    len = len + 1;
    
    for (i=0; i<len; i++)
    {
        data[i] = readRegister(addr);
        addr++;
    }
    
    *rxBuffer = (char *)data;
    
    return 0;
}

int EEPROM::writeEEPROM(unsigned int addr, unsigned int len, string txBuffer)
{
    unsigned int i;
    unsigned char *data = (unsigned char *)txBuffer.c_str();
    
    len = len + 1;
    
    for (i=0; i<len; i++)
    {
        writeRegister(addr, data[i]);
        addr++;
    }

    return 0;
}



int EEPROM::readEEPROM(unsigned int addr, unsigned int len, int *rxBuffer)
{
    unsigned int i;
    
    for (i=0; i<len; i++)
    {
        rxBuffer[i] = readRegister(addr);
        addr++;
    }
    
    return 0;
}

int EEPROM::writeEEPROM(unsigned int addr, unsigned int len, int txBuffer[])
{
    unsigned int i;
    
    for (i=0; i<len; i++)
    {
        writeRegister(addr, txBuffer[i]);
        addr++;
    }

    return 0;
}



EEPROM::~EEPROM()
{
    
}
