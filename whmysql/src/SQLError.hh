#ifndef _SQL_ERROR_
#define _SQL_ERROR_

#include <string>
#include "WhSQL.hh"


/**
 *  This class handles an error as an objet passed to SQLErrorHandler
 */

class whsql::SQLError
{
public:

        /**
         *  Constructs an SQLError based on the handler
         *  @param mysql MYSQL Instance
         */

         SQLError(MYSQL *mysql);


        /**
         *  Constructs an SQLError based on a type and a message
         *  @param type Some error type.
         *  @param msg  Some message.
         */

         SQLError(std::string type, std::string msg);


        /**
         *  Sets the error type
         *  @param type Some error type.
         */

         void setType(std::string type);


        /**
         *  Gets the error type
         *  @param type Some error type.
         */

         void setMessage(std::string msg);


        /**
         *  Sets the error type
         *  @return Some error type.
         */

         std::string getType();


        /**
         *  Sets the error type
         *  @return  An error message.
         */

         std::string getMessage();


        /**
         *  Prints the error type and message.
         *  @return  An error message.
         */

         void print();

protected:
/**
 * Contains the error type
 */
std::string m_errType;

/**
 * Contains the error message.
 */
std::string m_msg;
};
#endif
