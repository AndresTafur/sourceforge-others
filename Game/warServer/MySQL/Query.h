#ifndef _QUERY_H_
#define _QUERY_H_

#include <mysql/mysql.h>
#include <vector>

#include "ResultRow.h"

class Query
{
protected:

        Query(MYSQL *handler,std::string query);

public:

    void doQuery();

    void setParameter(std::string param, std::string value);

    std::vector<ResultRow> getResultList();

    ResultRow getSingleResult();

private:
std::string m_query;
MYSQL_RES  *m_resultSet;
MYSQL      *m_handler;
std::vector<ResultRow> m_rows;

friend class MySQL;
};
#endif
