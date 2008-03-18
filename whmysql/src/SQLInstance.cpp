#include "SQLInstance.hh"


        whsql::SQLInstance *whsql::SQLInstance::sm_instance = 0;


        whsql::SQLInstance::SQLInstance()
        {
                mysql_init(&m_handler);
        }


        whsql::SQLInstance* whsql::SQLInstance::getInstance()
        {
            if( !sm_instance)
                sm_instance = new SQLInstance();

            return sm_instance;
        }


        MYSQL whsql::SQLInstance::getHandler()
        {
            return m_handler;
        }

        void whsql::SQLInstance::onError( SQLError err)
        {
            err.print();
        }
