
#include "WhiteHawkNetClientStream.h"


#ifndef _WhiteHawkClientSocket_
#define _WhiteHawkClientSocket_

class WhiteHawkClientSocket : public WhiteHawkNetClientStream
{
public:    
    
    WhiteHawkClientSocket(WhiteHawkClientSocket *previous = NULL,WhiteHawkClientSocket *next = NULL);
  

    WhiteHawkClientSocket* GetPrevious();
    WhiteHawkClientSocket* GetNext();
    
    void Propagate(std::string data);
    void Propagate(WhiteHawkNetData data);
    
    void PropagateTo(std::string data,long id);
    void PropagateTo(WhiteHawkNetData data, long id);
    
   void PropagateEx(std::string data,long id);
   void PropagateEx(WhiteHawkNetData data, long id);    

    
    void SetPrevios(WhiteHawkClientSocket *previous);
    void SetNext(WhiteHawkClientSocket* next);
    

    void OnConnect(WhiteHawkNetEvt evt);
    void OnDisconnect(WhiteHawkNetEvt evt);
    void OnError(WhiteHawkNetEvt evt);
    void OnDataArrival(WhiteHawkNetEvt evt);
    void OnDataSent(WhiteHawkNetEvt evt);
    void OnClose(WhiteHawkNetEvt evt);
    
    
protected:

    void ifClosed();

WhiteHawkClientSocket *before;    
WhiteHawkClientSocket *after;
    
};

#endif
