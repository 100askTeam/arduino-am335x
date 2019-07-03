
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
    }  
        
    if (ev.type == EV_KEY) 
    {
        this->code  = ev.code;
        this->value = ev.value;
        
        //cout<<"code:"<<this->code<<endl;
        //cout<<"value:"<<this->value<<endl;
    }
    
    return 0;
}