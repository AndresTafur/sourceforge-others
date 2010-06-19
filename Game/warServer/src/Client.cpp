#include "Client.h"

Client::Client(SOCKET sock, struct sockaddr address)
{
    m_sock = sock;
    m_address = address;
}


void Client::Send(std::string data)
{
    send(m_sock,data.c_str(),300,MSG_OOB);
}

Client::~Client()
{
    //dtor
}
