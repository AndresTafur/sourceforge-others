#include "SQLServerSession.hh"
#include "SQLInstance.hh"

     whsql::SQLServerSession::SQLServerSession()
     {
        m_mysql = SQLInstance::getInstance()->getHandler();
        this->setErrorHandler(this);
     }



     bool whsql::SQLServerSession::connect(std::string user, std::string pass, std::string host,std::string db, short port)
     {

            if( NULL != mysql_real_connect(&m_mysql, host.c_str(),user.c_str(),pass.c_str(), db.c_str(), port, NULL, 0))
                    return true;
            /*
            m_errhndl->onError( SQLError(m_mysql) );
            return false;*/
     }



     bool whsql::SQLServerSession::isAlive()
     {
        if( mysql_ping(&m_mysql) == 0)
                return true;

        m_errhndl->onError( SQLError(&m_mysql) );
        return false;
     }


     bool whsql::SQLServerSession::changeUser(std::string user, std::string pass, std::string db)
     {
            if(mysql_change_user(&m_mysql,user.c_str(),pass.c_str(), db.c_str()) == 0)
                return true;

            m_errhndl->onError( SQLError(&m_mysql) );
            return false;
     }


     bool whsql::SQLServerSession::selectDatabase(std::string dbname)
     {
            if( mysql_select_db(&m_mysql, dbname.c_str()) == 0)
                return true;

            m_errhndl->onError( SQLError(&m_mysql) );
            return false;
     }


     void whsql::SQLServerSession::setSSL(std::string key, std::string cert, std::string cauto,std::string capath, std::string ciph)
     {
        mysql_ssl_set(&m_mysql,key.c_str(),cert.c_str(),cauto.c_str(),capath.c_str(),ciph.c_str());
     }


     void whsql::SQLServerSession::onError(SQLError err)
     {
            err.print();
     }
