#include "WhiteHawkNetEvtListener.h"


#ifndef _WhiteHawkNetServerListener_
#define _WhiteHawkNetServerListener_

class WhiteHawkNetServerListener : public WhiteHawkNetEvtListener
{
public:    
    
    virtual void OnListen(WhiteHawkNetEvt evt) = 0;
    

    virtual ~WhiteHawkNetServerListener(){}

};

#endif
