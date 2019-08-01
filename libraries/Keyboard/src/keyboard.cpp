
#include "keyboard.h"

KEYBOARD::KEYBOARD()
{
    this->m_sPath = KEYBOARD_EVENT_PATH;
    
    this->m_iFileEvent = open(KEYBOARD_EVENT_PATH, O_RDONLY);  
    if (this->m_iFileEvent < 0) {  
        perror("KEYBOARD: open file failed\n");  
    }  
}

KEYBOARD::~KEYBOARD(void)
{
    close(this->m_iFileEvent);
}

int KEYBOARD::readKey(void)
{
    int ret;
    struct input_event ev;
    
    ret = read(this->m_iFileEvent , &ev, sizeof(struct input_event));  
    if (ret < 0) {  
        perror("KEYBOARD: read event error!\n"); 
        return -1;
    }  
        
    if (ev.type == EV_KEY) 
    {
        this->m_iCode  = ev.code;
        this->m_iValue = ev.value;

        return 0;
    }
    else 
        return 0;
}

int KEYBOARD::getCode(void)
{
    return this->m_iCode;
}

int KEYBOARD::getValue(void)
{   
    return this->m_iValue;  
}

