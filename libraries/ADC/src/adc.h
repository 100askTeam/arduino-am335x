#ifndef _ADC_H
#define _ADC_H

#include <Arduino.h>

#define ADC1_PATH  "/sys/devices/platform/ocp/44e0d000.tscadc/TI-am335x-adc/iio:device0/in_voltage4_raw"
#define ADC2_PATH  "/sys/devices/platform/ocp/44e0d000.tscadc/TI-am335x-adc/iio:device0/in_voltage5_raw"

class ADC {
    private:
        string m_sPath;
        int m_iFile;
        int m_iValue;

    public:
        ADC(int num);
        ~ADC(void);
        
        int getValue(void);
};

#endif