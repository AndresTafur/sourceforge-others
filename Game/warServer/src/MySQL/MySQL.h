#ifndef _PA_MYSQL_H_
#define _PA_MYSQL_H_

#include <string>
#include "Query.h"

class MySQL
{
protected:

            MySQL();

public:

            static MySQL* getInstancePtr();

            bool connect(std::string user, std::string password, const char *database = NULL, std::string server = "localhost", int port = 3306);

            Query* createQuery(std::string query);

            void destroy();

private:
MYSQL *m_handler;
static MySQL *sm_instance;
};
#endif
