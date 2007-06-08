#include "whiteSQL.hh"


   /** Default constructor
	* Sets the engine event manager and the initialized Sql
	* @param  evt   EventManager
	* @param  init  Initialized SQL manager
	* @see    whiteSQL::SqlInitialized
	* @see    whiteSQL::SqlEngineEvent
    */

    whiteSQL::SqlEngine::SqlEngine(SqlEngineEvent *evt, SqlInitialized *init)
    {
	    this->event = evt;
	    this->init  = init;
    }


      /** Connects to the MySQL server and tests the MySQL initial structure
	*
	* @param  host Host to connect, (specify "localhost" or "127.0.0.1"if the server is in the same machine)
	* @param  port  Port to connect (by default is the 3306)
	* @param  user  Username to connect (by default is root)
	* @param  pass  Password to connect (by default is empty)
	* @see    whiteSQL::SqlInitialized
        */

	void whiteSQL::SqlEngine::Connect(std::string host, int port, std::string user, std::string pass)
	{
	  mysql_real_connect(init->Get(),host.c_str(),user.c_str(),pass.c_str(),NULL,port,NULL,0);
	 	 if( init->isNull() )
			this->procError();
	}


      /** Organize and set the query on a "printf" style,
	* after that makes the query (using makeQuery()) and stores the result
	*
	* @param  str  string containing the query (formatted as printf)
	* @param  ...  other strings (must be const char*) for replace in the query
	* @return  The result of the query
	* @see    whiteSQL::SqlResult
	* @see    makeQuery()
        */

        whiteSQL::SqlResult* whiteSQL::SqlEngine::doQuery(std::string str, ...)
        {
            va_list list;
            int index;

            va_start(list,str);

	    while( ( index = str.find("%s",0) )!= std::string::npos )
                     str.replace(index,2,va_arg(list,char*) );

            va_end(list);


	 return makeQuery(str);
       }

      /** Test the connection (with isAlive()), makes the query
	* and stores the result
	*
	* @param  str2  string containing the query
	* @return  The result of the query
	* @see    whiteSQL::SqlResult
	* @see    isAlive()
        */
	whiteSQL::SqlResult* whiteSQL::SqlEngine::makeQuery(std::string str2)
	{
		if(this->isAlive())
			if( mysql_query(init->Get(),str2.c_str()) != 0)
				this->procError();
			else
			{
		    	  SqlResult *result;
		    	  MYSQL_RES *res;

		        	res = mysql_store_result(init->Get());
				if( res != NULL )
				{
        	    			result = new SqlResult( res );
			        	return result;
				}
			}
	  return NULL;
	}



      /** Tests if the conecction is alive (and tries to reconnect)
	* @return  true if the connection is OK false otherwise
        */
      bool whiteSQL::SqlEngine::isAlive()
      {
	 if(init->Get())
	   if( mysql_ping(init->Get()) == 0)
		return true;

	 SqlEvtType *evt = new SqlEvtType(2055,"Lost connection to MySQL server");
	 event->OnError(evt);
	return false;
      }


      /** This method process the kind of error
	* and send it to the Event manager
        */

      void whiteSQL::SqlEngine::procError()
      {
	  SqlEvtType *evt = new SqlEvtType(mysql_errno(init->Get()),mysql_error(init->Get()));
		event->OnError(evt);
      }
