#include "WhiteHawkClient.h"


            WhiteHawkClient::WhiteHawkClient() : WhiteHawkNetClientStream()
            {
                this->SetListener(this);
            }

            WhiteHawkClient::WhiteHawkClient(WhiteHawkNetEvtListener *listener) : WhiteHawkNetClientStream()
            {
                this->SetListener(listener);
            }
    
    
            bool WhiteHawkClient::Connect()
            {
               return this->Connect(remote);
            }

            bool WhiteHawkClient::Connect(WhiteHawkNetAddress *address)
            {
                struct  sockaddr_in addr = address->GetAddress();
                if( SOCKET_ERROR == connect(handler, (SOCKADDR*)&addr, sizeof(addr) ) )
                {
                    listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("CONNECTION ERROR"), NET_CONNECT_ERROR) );
                    return false;
                }

                this->Create();
                remote = address;
                listener->OnConnect(WhiteHawkNetEvt( WhiteHawkNetData("Connected"), NET_EVT_CONNECT));
                
                return true;
            }
    
    
            bool WhiteHawkClient::Disconnect()
            {
              if( closesocket(handler) == 0)
                return true;
            
              return false;
            }
    
            void WhiteHawkClient::ifClosed()
            {

            }

                     
  
            void WhiteHawkClient::OnConnect(WhiteHawkNetEvt evt)
            {
                std::cout << evt.GetData() << std::endl;    
            }
            void WhiteHawkClient::OnDisconnect(WhiteHawkNetEvt evt)
            {
              std::cout << " We are disconnected from " << remote->GetIpAddress() << " at port " << remote->GetPort();
            }
            void WhiteHawkClient::OnError(WhiteHawkNetEvt evt)
            {
              std::cout << "WhiteHawkNetworkError: " << evt.GetId() << " [ " << evt.GetData() << " ]" <<  std::endl << std::endl;  
            }
            void WhiteHawkClient::OnDataArrival(WhiteHawkNetEvt evt)
            {
              std::cout << evt.GetData() << std::endl;  
            }    
            void WhiteHawkClient::OnDataSent(WhiteHawkNetEvt evt)
            {
                std::cout << evt.GetData() << std::endl; 
            }
            void WhiteHawkClient::OnClose(WhiteHawkNetEvt evt)
            {
                std::cout << evt.GetData() << std::endl; 
            }
