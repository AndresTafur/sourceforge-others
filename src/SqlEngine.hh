
/**
 *  This class set's a basic interface to comunicate with the mysql server
 *  It's in low level of the class implementation,and it's the base of
 *  all the managers in whiteSQL
 */


class whiteSQL::SqlEngine
{
public:


   /** Default constructor
    *  Sets the engine event manager and the initialized Sql
    *  @param  evt   EventManager
    * @param  init  Initialized SQL manager
    * @see    whiteSQL::SqlInitialized
    * @see    whiteSQL::SqlEngineEvent
    */

    SqlEngine(SqlEngineEvent *evt, SqlInitialized *init);


      /** Connects to the MySQL server and tests the MySQL initial structure
	*
	* @param  host Host to connect, (specify "localhost" or "127.0.0.1"if the server is in the same machine)
	* @param  port  Port to connect (by default is the 3306)
	* @param  user  Username to connect (by default is root)
	* @param  pass  Password to connect (by default is empty)
	* @see    whiteSQL::SqlInitialized
        */

	void Connect(std::string host, int port, std::string user, std::string pass);



      /** Organize and set the query on a "printf" style,
	* after that makes the query (using makeQuery()) and stores the result
	*
	* @param  str  string containing the query (formatted as printf)
	* @param  ...  other strings (must be const char*) for replace in the query
	* @return  The result of the query
	* @see    whiteSQL::SqlResult
	* @see    makeQuery()
        */

        SqlResult* doQuery(std::string str, ...);

protected:


      /** Test the connection (with isAlive()), makes the query
	* and stores the result
	*
	* @param  str2  string containing the query
	* @return  The result of the query
	* @see    whiteSQL::SqlResult
	* @see    isAlive()
        */
	SqlResult* makeQuery(std::string str2);



      /** Tests if the conecction is alive (and tries to reconnect)
	* @return  true if the connection is OK false otherwise
        */
      bool isAlive();


      /** This method process the kind of error
	* and send it to the Event manager
        */

      void procError();

protected:

 /*
  * Event and error manager
  */
 SqlEngineEvent *event;

 /*
  * Pointer to an initialized MySQL connection
  */
 SqlInitialized *init;
};
