#include "WhiteHawkNetClientStream.h"

       void WhiteHawkNetClientStream::ThreadRoutine()
        {
           char recvbuff[32];
           WhiteHawkNetData str;

            while(true)
            {
             if( this->CheckSocket() )

                if( SOCKET_ERROR == recv( handler, recvbuff, 32, 0))
                {
                    listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("RECEIVE ERROR"), NET_REC_ERROR) );
                    listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("REMOTE DOWN"), NET_REMOTE_ERROR) );
                    listener->OnDisconnect( WhiteHawkNetEvt( WhiteHawkNetData("SOCKET CLOSED"), NET_EVT_DISCONNECT));
                    break;
                }
                else
                    str = WhiteHawkNetData(recvbuff);

              listener->OnDataArrival( WhiteHawkNetEvt(str,this->GetId()));
            }

        }
        
       void WhiteHawkNetClientStream::SetId(long id)
        {
            this->clientID = id;
        }  

        long WhiteHawkNetClientStream::GetId()
        {
            return clientID;
        }

       void WhiteHawkNetClientStream::Send(std::string str)
        {
            if( this->CheckSocket() )
               if( SOCKET_ERROR == send( handler, str.c_str(), 32, 0))
                     listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("Socket error"), NET_SEND_ERROR) );
               else     
                    listener->OnDataSent( WhiteHawkNetEvt( WhiteHawkNetData("Data sent"), NET_EVT_DATASENT) );
        }

        void WhiteHawkNetClientStream::Send(WhiteHawkNetData str)
        {
            if( this->CheckSocket() )
               if( SOCKET_ERROR == send( handler, str.c_str(), 32, 0))
                     listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("Socket error"), NET_SEND_ERROR) );
               else
                    listener->OnDataSent( WhiteHawkNetEvt( WhiteHawkNetData("Data sent"), NET_EVT_DATASENT) );
        }
        

        void WhiteHawkNetClientStream::operator << (std::string str)
        {
                this->Send(str);
        }


        void WhiteHawkNetClientStream::operator << (WhiteHawkNetData str)
        {
             this->Send(str);
        }
