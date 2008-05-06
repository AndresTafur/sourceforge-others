#include "WhiteHawkNetServerStream.h"


    WhiteHawkNetServerStream::WhiteHawkNetServerStream() : WhiteHawkNetSocketStream()
    {
        list = NULL;
        listener = this;
    }

    void WhiteHawkNetServerStream::Send(std::string str)
    {
               if( this->CheckSocket() )
                  if( NULL != list)  
                    list->Propagate(str);    
                  else
                    listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("There is no connected clients"), NET_SEND_ERROR) );
               else
                  listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("Socket error"), NET_SOCKET_ERROR) );
     }

     void WhiteHawkNetServerStream::Send(WhiteHawkNetData str)
     {
               if( this->CheckSocket() )
                  if( NULL != list)
                    list->Propagate(str);
                  else
                    listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("There is no connected clients"), NET_SEND_ERROR) );
               else
                  listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("Socket error"), NET_SOCKET_ERROR) );
     }
     
     
     void WhiteHawkNetServerStream::SendTo(std::string str, long id)
     {
               if( this->CheckSocket() )
                  if( NULL != list)
                    list->PropagateTo(str,id);
                  else
                    listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("There is no connected clients"), NET_SEND_ERROR) );
               else
                  listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("Socket error"), NET_SOCKET_ERROR) );
     }
     
     void WhiteHawkNetServerStream::SendTo(WhiteHawkNetData str, long id)
     {
               if( this->CheckSocket() )
                  if( NULL != list)
                    list->PropagateTo(str,id);
                  else
                    listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("There is no connected clients"), NET_SEND_ERROR) );
               else
                  listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("Socket error"), NET_SOCKET_ERROR) );
     }
     
     
     void WhiteHawkNetServerStream::SendEx(WhiteHawkNetData str, long id)
     {
            if( this->CheckSocket() )
                  if( NULL != list)
                    list->PropagateEx(str,id);
                  else
                    listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("There is no connected clients"), NET_SEND_ERROR) );
               else
                  listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("Socket error"), NET_SOCKET_ERROR) );       
     }
    
    
     void WhiteHawkNetServerStream::SendEx(std::string str, long id)
     {
           if( this->CheckSocket() )
                  if( NULL != list)
                    list->PropagateEx(str,id);
                  else
                    listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("There is no connected clients"), NET_SEND_ERROR) );
               else
                  listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("Socket error"), NET_SOCKET_ERROR) );            
     }
     

     void WhiteHawkNetServerStream::operator << (std::string str)
     {
                this->Send(str);
     }


     void WhiteHawkNetServerStream::operator << (WhiteHawkNetData str)
     {
             this->Send(str);
     }
