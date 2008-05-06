#include "WhiteHawkServer.h"


            WhiteHawkServer::WhiteHawkServer() : WhiteHawkNetServerStream()
            {
                   local  = new WhiteHawkNetAddress();
                  this->listener = this;
            }

            bool WhiteHawkServer::Listen()
            {
               return this->Listen(local);        
            }
            
           
             bool WhiteHawkServer::Listen(WhiteHawkNetAddress *address)
             {
                 struct  sockaddr_in addr = address->GetAddress();    
                    
                 if ( bind(handler,(SOCKADDR*) &addr, sizeof(addr)) == SOCKET_ERROR) 
                 {
                    listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("BIND ERROR"), NTE_BIND_ERROR) );
                    return false;
                 }   
                    
                 if (listen( handler, 65535 ) == SOCKET_ERROR)
                 {
                    listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("LISTEN ERROR"), NET_LISTEN_ERROR) );
                    return false;
                 }
                 
                 listener->OnListen( WhiteHawkNetEvt( WhiteHawkNetData("SERVER WAITING FOR CONNECTIONS"),  NET_EVT_LISTEN));
                 this->Create();
                 return true;
             }
             
             
             long WhiteHawkServer::GetClientCount()
             {
                 if(list)   
                   return list->GetId();       
                 else
                   return 0;
             }
             
             
             void WhiteHawkServer::ThreadRoutine()
             {
                 while(true)
                 {

                    clientSocket = accept( handler, NULL, NULL );

                    if(  clientSocket == INVALID_SOCKET)
                        listener->OnError( WhiteHawkNetEvt( WhiteHawkNetData("CONNECTION ERROR"), NET_CONNECT_ERROR) );
                    else
                    {
                        WhiteHawkClientSocket *ptr = NULL;
                        long clid = 0;


                            if( list != NULL)
                            {
                                ptr  = list;
                                list = list->GetNext();
                                clid = ptr->GetId() + 1;
                                
                            }
                     
                            list = new WhiteHawkClientSocket(ptr);

                            
                            list->SetId( clid );
                            list->SetHandler(clientSocket);
                            list->SetListener(listener);

                            //printf("%i",list->GetPrevious()->GetId());
                            list->Create();
                            listener->OnConnect(WhiteHawkNetEvt(WhiteHawkNetData("Client connected"), NET_EVT_CONNECT));
                       }

                 }

            }
             
     
            void WhiteHawkServer::OnConnect(WhiteHawkNetEvt evt)
            {
                std::cout << "WhiteHawkServer: " << evt.GetId() << "[ " << evt.GetData() << " ]" << std::endl; 
                std::cout << "Client ID: " << list->GetId();                
                list->Propagate("\n Hola");

            }
            
            void WhiteHawkServer::OnDisconnect(WhiteHawkNetEvt evt){}
            void WhiteHawkServer::OnError(WhiteHawkNetEvt evt)
            {
                std::cout << "WhiteHawkServerError: " << evt.GetId() << "[ " << evt.GetData() << " ]" << std::endl;    
            }
            void WhiteHawkServer::OnListen(WhiteHawkNetEvt evt)
            {
                std::cout << "WhiteHawkServer: " << evt.GetId() << "[ " << evt.GetData() << " ]" << std::endl; 
            }
            void WhiteHawkServer::OnDataArrival(WhiteHawkNetEvt evt)
            {
                std::cout << "WhiteHawkServer: " << evt.GetId() << "[ " << evt.GetData() << " ]" << std::endl;   
                SendEx( evt.GetData(), evt.GetId());
            }
            void WhiteHawkServer::OnDataSent(WhiteHawkNetEvt evt){}
            void WhiteHawkServer::OnClose(WhiteHawkNetEvt evt){}

  
