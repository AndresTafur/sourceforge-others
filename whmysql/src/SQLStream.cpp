#include "SQLStream.hh"
#include "SQLError.hh"



        whsql::SQLStream::SQLStream() : whsql::SQLServerSession::SQLServerSession()
        {

        }


        bool whsql::SQLStream::commit()
        {
             return mysql_commit(&m_mysql);
        }

        bool whsql::SQLStream::autoCommit(bool val)
        {
            return !mysql_autocommit(&m_mysql, val);
        }

        bool whsql::SQLStream::rollback()
        {
                return !mysql_rollback(&m_mysql);
        }



        whsql::SQLResult& whsql::SQLStream::fetch(whsql::SQLResult &str)
        {
          int num_fields = mysql_num_fields(m_result);

            if( num_fields > 0)
                while ((m_row = mysql_fetch_row(m_result)))
                {
                   whsql::SQLResultRow sqlrow;

                    for(int i = 0; i < num_fields; i++)
                        sqlrow.insertValue(m_row[i]);

                    str << sqlrow;
                }
                mysql_free_result(m_result);

           return str;
        }

        void whsql::SQLStream::operator << (whsql::SQLQuery &query)
        {
           std::string str = query.getQuery();
           whsql::SQLResult res;
           int aff;

                if( mysql_real_query(&m_mysql, str.c_str(),str.length()) != 0)
                    m_errhndl->onError( SQLError(&m_mysql) );
                else
                {
                    if( (m_result = mysql_store_result(&m_mysql)) != NULL)
                    {
                        fetch(res);
                        query.setResult(res);
                    }
                    else
                    {
                        if( mysql_field_count(&m_mysql) == 0)
                        {
                                aff = mysql_affected_rows(&m_mysql);
                                res.setAffected(aff);
                                query.setResult(res);
                        }
                        else
                            m_errhndl->onError( SQLError(&m_mysql) );
                    }

                }
        }


        void whsql::SQLStream::operator << (std::string str)
        {
                if( mysql_real_query(&m_mysql, str.c_str(),str.length()) != 0)
                    m_errhndl->onError( SQLError(&m_mysql) );
                else
                {
                    if( (m_result = mysql_store_result(&m_mysql)) == NULL)
                        if( mysql_field_count(&m_mysql) != 0)
                            m_errhndl->onError( SQLError(&m_mysql) );
                }
        }


        whsql::SQLResult&  whsql::SQLStream::operator >> ( whsql::SQLResult &str)
        {
            str = fetch(str);
            return str;
        }
