#ifndef _OLED_H
#define _OLED_H

#include <Arduino.h>
#include "font.h"
#include "spi.h"
#include "gpio.h"

class OLED : public SPI {
private:
    int m_iPage;
    int m_iCol;
    string m_pStr;
    int m_SPInum;
    GPIO m_cDCPin;

private:
    void setDC(char val);
    void writeCmd(unsigned char cmd);
    void writeData(unsigned char data);
    void setPageAddrMode(void);
    void setPos(int page, int col);
    void putChar(int page, int col, char c);
    void OLEDInit(void);
    
public:
    OLED(int num);
    virtual void OLEDPrint(int page = 0, int col = 0, string = " ");
    virtual void OLEDClearAll(void);
    virtual void OLEDClearPage(int page);
    virtual ~OLED();
};

    
#endif