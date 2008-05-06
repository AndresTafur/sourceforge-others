#include "SQLError.hh"
#include <iostream>

         whsql::SQLError::SQLError(MYSQL *mysql)
         {
             m_errType = mysql_errno(mysql);
             m_msg = mysql_error(mysql);
         }


         whsql::SQLError::SQLError(std::string type, std::string msg)
         {
             m_errType = type;
             m_msg = msg;
         }

         void whsql::SQLError::setType(std::string type)
         {
                m_errType = type;
         }

         void whsql::SQLError::setMessage(std::string msg)
         {
                m_msg = msg;
         }

         std::string whsql::SQLError::getType()
         {
                return m_errType;
         }

         std::string whsql::SQLError::getMessage()
         {
               return m_msg;
         }


         void whsql::SQLError::print()
         {
            std::string error = "Error Type";

                //TODO: fix this (not using cerr for avoiding iostream)

                    error += m_errType;
                    error += "\nError message: ";
                    error += m_msg;

                    perror( error.c_str());
         }
