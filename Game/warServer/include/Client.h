#ifndef _THIRDWAR_CLIENT_H__
#define _THIRDWAR_CLIENT_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define SOCKET int
#include "Thread.h"

class Client : public ThirdWar::Thread
{
public:
        /** Default constructor */
        Client(SOCKET sock, struct sockaddr address);


        inline SOCKET getSocket() { return m_sock;}

        void Send(std::string data);

        /** Default destructor */
        virtual ~Client();


private:
SOCKET m_sock;
struct sockaddr m_address;
};

#endif // _THIRDWAR_CLIENT_H__
