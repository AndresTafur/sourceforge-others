#include "ClientAttender.h"
#include <iostream>




        void ClientAttender::run()
        {
            SOCKET sock = m_client->getSocket();
            char buffer[300];


            while(m_running)
            {
                 if( recv(sock, buffer, 300, MSG_WAITALL) == 0)
                 {
                     //TODO: Inform Server about this so its been remove from the multicast queue.
                    std::cerr << "\nSocket has been shuted unexpectly down.\n";
                    m_running = false;
                 }
                 else
                    attend(buffer);
            }


        }
