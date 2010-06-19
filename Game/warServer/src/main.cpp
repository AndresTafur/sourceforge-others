#include "MySQL/MySQL.h"
#include <iostream>
#include "Server.h"

class WarAttender : public ClientAttender
{
public:

        void attend(std::string data)
        {

            fprintf(stderr,"Hola cliente %i tus datos son %s.", m_client->getSocket(),data.c_str());
        }

};



class ClientsBuilder : public ClientAttenderBuilder
{
public:

    ClientAttender* getClientAttender()
    {
        return new WarAttender();
    }

};


int main()
{
MySQL *obj;
Query *quer;
ResultRow fila;
Server *serv = Server::getInstancePtr();


     obj = MySQL::getInstancePtr();
     obj->connect("root","1234","3rdwar");

     quer = obj->createQuery("select * from :entity");
     quer->setParameter(":entity","Player");

    try
    {
        serv->Listen(2588);
        serv->setClientBuilder(new ClientsBuilder());

//        quer->doQuery();
//        fila = quer->getSingleResult();
//       printf("%s\n", fila["password"].c_str() );
        getchar();
        serv->destroy();
    }
    catch(std::string str)
    {
        std::cerr << str;

    }

     getchar();
}
