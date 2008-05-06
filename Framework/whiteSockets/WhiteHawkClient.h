
#include "WhiteHawkNetClientStream.h"

#ifndef _WhiteHawkSocketClient_
#define _WhiteHawkSocketClient_

class WhiteHawkClient : public WhiteHawkNetClientStream 
{
public:
            WhiteHawkClient();
            
            WhiteHawkClient(WhiteHawkNetEvtListener *listener);
    
            bool Connect();
            bool Connect(WhiteHawkNetAddress *address);
            bool Disconnect();
           
            
    
            void OnConnect(WhiteHawkNetEvt evt);
            void OnDisconnect(WhiteHawkNetEvt evt);
            void OnError(WhiteHawkNetEvt evt);
            void OnDataArrival(WhiteHawkNetEvt evt);    
            void OnDataSent(WhiteHawkNetEvt evt);
            void OnClose(WhiteHawkNetEvt evt);

protected:
            void ifClosed();

}; 
#endif
