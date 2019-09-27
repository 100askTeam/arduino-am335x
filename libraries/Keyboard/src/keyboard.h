#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <Arduino.h>

#define KEY1 (105)
#define KEY2 (106)
#define KEY3 (28)
#define KEY4 (1)

#define KEYBOARD_EVENT_PATH   "/dev/input/event"

class KEYBOARD  {
    private:
        string m_sPath;
        int m_iFileEvent;
        int m_iCode;
        int m_iValue;
    
    public:
        KEYBOARD();
        virtual int readKey(void);
        virtual int getCode(void);
        virtual int getValue(void);
        ~KEYBOARD(void);
};

int getEventNumber(char *name);

#endif 


