#include "WhiteHawkNetObject.h"
#include "WhiteHawkNetEvt.h"

#ifndef _WhiteHawkNetEvtListener_
#define _WhiteHawkNetEvtListener_

class WhiteHawkNetEvtListener : public WhiteHawkNetObject
{
public:    
    
        virtual void OnConnect(WhiteHawkNetEvt evt) = 0;
        virtual void OnDisconnect(WhiteHawkNetEvt evt) = 0;
        virtual void OnDataArrival(WhiteHawkNetEvt evt) = 0;
        virtual void OnClose(WhiteHawkNetEvt evt) = 0;
        virtual void OnError(WhiteHawkNetEvt evt) = 0;
        virtual void OnDataSent(WhiteHawkNetEvt evt) = 0;
   
        virtual ~WhiteHawkNetEvtListener(){}
};
#endif
