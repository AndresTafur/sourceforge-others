#ifndef _SQLINSTANCE_
#define _SQLINSTANCE_

#include "WhSQL.hh"
#include "SQLErrorHandler.hh"
#include "SQLError.hh"


/**
 *  This class manages the MYSQL instance using a singleton pattern
 *  should be statically called when the instance is needed.
 */


class whsql::SQLInstance : public whsql::SQLErrorHandler
{
private:

            /**
             *  Construct's an SQLInstance object
             */

            SQLInstance();

public:

            /**
             *  Get's the current instance, creates one if none,
             *  should be accesed in a statical way.
             */

            static whsql::SQLInstance* getInstance();


            /**
             *  Get's the MYSQL Ansi C handler
             */

            MYSQL getHandler();


            /**
             *  inherits from SQLErrorHandler, we must implement this method.
             *  will print the error message and type.
             */

            void onError( SQLError err);

protected:
/**
 *  The MYSQL Ansi C handler.
 */

MYSQL m_handler;

/**
 *  The instance (see singleton).
 */
static SQLInstance *sm_instance;

};

#endif
