#include "SQLQuery.hh"



        void whsql::SQLQuery::setResult( whsql::SQLResult &res)
        {
             m_res = res;
        }

        void whsql::SQLQuery::setQuery(std::string query)
        {
             m_query = query;
        }


        void whsql::SQLQuery::operator = (std::string str)
        {
            m_query = str;
        }

        whsql::SQLResult& whsql::SQLQuery::operator >> (whsql::SQLResult &res)
        {
            res = m_res;
            return res;

        }
