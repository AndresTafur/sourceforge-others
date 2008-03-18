#ifndef _SQL_STREAM_
#define _SQL_STREAM_

#include "WhSQL.hh"
#include "SQLServerSession.hh"
#include "SQLResult.hh"
#include "SQLQuery.hh"

class whsql::SQLStream : public whsql::SQLServerSession
{
public:

        SQLStream();

        bool commit();

        bool autoCommit(bool val);

        bool rollback();


        void operator << (whsql::SQLQuery &query);

        void operator<<(std::string str);

        whsql::SQLResult& operator>>(whsql::SQLResult &result);

protected:

        whsql::SQLResult& fetch(whsql::SQLResult &str);

protected:
MYSQL_RES *m_result;
MYSQL_ROW  m_row;
};

#endif
