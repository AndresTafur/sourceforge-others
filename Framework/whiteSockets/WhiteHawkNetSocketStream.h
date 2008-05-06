#include "config.h"

#include "WhiteHawkNetEvtListener.h"
#include "WhiteHawkNetAddress.h"

#ifndef _WhiteHawkNetSocketStream_
#define _WhiteHawkNetSocketStream_

class WhiteHawkNetSocketStream : public WhiteHawkNetEvtListener
{
public:
    
    WhiteHawkNetSocketStream(); 
 
    bool CheckSocket();
    void SetListener(WhiteHawkNetEvtListener *listener);
    void SetHandler( SOCKET handler);
 
    virtual void Send(std::string str) = 0;
    virtual void Send(WhiteHawkNetData str) = 0 ;
 
    virtual void operator << (std::string str) = 0;
    virtual void operator << (WhiteHawkNetData str)    = 0;

    ~WhiteHawkNetSocketStream();

protected:
SOCKET handler;  
WhiteHawkNetEvtListener *listener; 
WhiteHawkNetAddress *local;
WhiteHawkNetAddress *remote;

};
#endif
