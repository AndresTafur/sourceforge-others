#ifndef _SQL_QUERY_
#define _SQL_QUERY_

#include "WhSQL.hh"
#include "SQLResult.hh"


/**
 *  This class manages sql query's and results.
 */

class whsql::SQLQuery
{
public:

        /**
         *  Changes the result assigned to this object.
         *  @param res New result object to be assigned.
         */

        void setResult(whsql::SQLResult &res);

        /**
         *  Set's the MySQL query of this object (same as operator =).
         *  @param query String of a MYSQL query.
         */

        void setQuery(std::string query);

        /**
         *  Get's the result of this query, none if this object
         *  is not passed througth a SQLStream object.
         *  @return SQLResult constructed by a SQLStream object.
         */

        inline whsql::SQLResult getResult() { return m_res; }

        /**
         *  Get's the query string of this object.
         */

        inline std::string getQuery() { return m_query; }


        /**
         *  Set's the MySQL query of this object.
         *  @param str String of a MYSQL query.
         */

        void operator = (std::string str);

        /**
         *  Returns a result of this query, this object must be passed
         *  throught an SQLStream before calling this operator.
         *  @param result object to manage the query result.
         *  @return  The query result.
         */

        whsql::SQLResult& operator >> (whsql::SQLResult &result);


protected:

/**
 *  A result object of the query
 */

whsql::SQLResult m_res;

/**
 *  MYSQL query string
 */

std::string m_query;
};
#endif
