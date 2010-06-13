#include "MySQL/MySQL.h"
#include <iostream>

int main()
{
MySQL *obj;
Query *quer;
ResultRow fila;



     obj = MySQL::getInstancePtr();
     obj->connect("root","1234","3rdwar");

     quer = obj->createQuery("select * from :entity");
     quer->setParameter(":entity","Player");


    try
    {
        quer->doQuery();
        fila = quer->getSingleResult();
        printf("%s\n", fila["password"].c_str() );

    }
    catch(std::string str)
    {
        std::cout << str;

    }

     getchar();

}
