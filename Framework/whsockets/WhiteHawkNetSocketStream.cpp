#include "WhiteHawkNetSocketStream.h"


        WhiteHawkNetSocketStream::WhiteHawkNetSocketStream()
        {
	  #ifdef WIN32
          WSADATA     wsaData;
          WSAStartup(MAKEWORD(2,2),&wsaData);
	  #endif
          handler = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            
           local  = new WhiteHawkNetAddress();
           remote = new WhiteHawkNetAddress();
        }
        
        void WhiteHawkNetSocketStream::SetListener(WhiteHawkNetEvtListener *listener)
        {
                this->listener = listener;
        }
        
        void WhiteHawkNetSocketStream::SetHandler( SOCKET handler)
        {
            this->handler = handler;    
        }
        
        
        bool WhiteHawkNetSocketStream::CheckSocket()
        {
            if( handler == INVALID_SOCKET )
            {
                listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("INVALID SOCKET"), NET_SOCKET_ERROR) );
                return false;
            }
            return true;
        }
        
        WhiteHawkNetSocketStream::~WhiteHawkNetSocketStream()
        {}
 
    
   
