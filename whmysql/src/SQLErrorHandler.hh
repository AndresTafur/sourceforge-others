#ifndef _SQLERROR_HANDLER_
#define _SQLERROR_HANDLER_

#include "WhSQL.hh"


/**
 *  This abstract manages all error notifications (SQLError objects)
 *  should be overriden for each class that manages MYSQL* intance directly.
 */

class whsql::SQLErrorHandler
{
public:


        /**
         *   Changes the error handler for the current object
         */

        void setErrorHandler(whsql::SQLErrorHandler *handler);


        /**
         *   This method is called when an error has been ocurred
         *   should be overriden by the user.
         */

        virtual void onError(SQLError evt) = 0;

public:
/**
 *  This atribute is the instance of the hanlder
 *  to be called when an error ocurrs.
 */
SQLErrorHandler *m_errhndl;

};


#endif
