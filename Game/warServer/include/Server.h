#ifndef _WAR_SERVER_H_
#define _WAR_SERVER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "Thread.h"
#include "ClientAttenderBuilder.h"

#define SOCKET int

class Server : public ThirdWar::Thread
{
private:
        /** Default constructor */
        Server();

public:

        static Server *getInstancePtr();

        static Server &getInstance();

        void Listen(unsigned int port);

        void run();

        void sendMulticast(std::string data);

        inline void setClientBuilder(ClientAttenderBuilder *blder) { m_builder = blder;}

        static void destroy();


        /** Default destructor */
        virtual ~Server();
    protected:



private:
  SOCKET m_sock;
  ClientAttenderBuilder *m_builder;
  struct sockaddr_in m_address;
  bool m_running;
  static Server* sm_instance;
  std::vector<Client*> m_clients;
};

#endif // _WAR_SERVER_H_
