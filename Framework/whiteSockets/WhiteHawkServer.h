#include "WhiteHawkThread.h"  
#include "WhiteHawkNetServerStream.h"  
#include "WhiteHawkClientSocket.h"

#ifndef _WhiteHawkSocketServer_
#define _WhiteHawkSocketServer_

class WhiteHawkServer : public WhiteHawkNetServerStream, public WhiteHawkNetServerListener,  public WhiteHawkThread
{
public:
            WhiteHawkServer();

            bool Listen();
            bool Listen(WhiteHawkNetAddress *address);
            
            
            void ThreadRoutine();
           
            long GetClientCount();

            void OnConnect(WhiteHawkNetEvt evt);
            void OnDisconnect(WhiteHawkNetEvt evt);
            void OnError(WhiteHawkNetEvt evt);
            void OnDataArrival(WhiteHawkNetEvt evt);
            void OnClose(WhiteHawkNetEvt evt);
            
            void OnListen(WhiteHawkNetEvt evt);
            void OnDataSent(WhiteHawkNetEvt evt);
           

protected:
WhiteHawkNetServerListener *listener;
WhiteHawkNetAddress     *local;


SOCKET clientSocket;
SOCKET handler;
};
#endif
