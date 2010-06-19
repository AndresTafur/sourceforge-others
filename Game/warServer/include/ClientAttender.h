#ifndef _CLIENTATTENDER_H_
#define _CLIENTATTENDER_H_

#include "Client.h"

class ClientAttender : public ThirdWar::Thread
{
public:

        virtual void attend(std::string data) = 0;

        inline void setClient(Client *clt) { m_client = clt;}

        inline Client* getClient() { return m_client;}

protected:

        void run();

protected:
Client *m_client;
bool m_running;

};

#endif // _CLIENTATTENDER_H_
