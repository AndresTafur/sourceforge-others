#ifndef _SQLSERVERSESSION_
#define _SQLSERVERSESSION_

#include "WhSQL.hh"
#include "SQLErrorHandler.hh"

class whsql::SQLServerSession  : public whsql::SQLErrorHandler
{
public:

            SQLServerSession();

            bool connect(std::string user, std::string pass, std::string host = "127.0.0.1",std::string db = "", short port = 3306);

            bool isAlive();

            bool changeUser(std::string user, std::string pass, std::string db="");

            bool selectDatabase(std::string dbname);

            void setSSL(std::string key, std::string cert, std::string cauto,std::string capath, std::string ciph);


protected:

            void onError(SQLError err);

protected:

MYSQL m_mysql;
};

#endif
