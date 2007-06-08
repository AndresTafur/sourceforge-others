#include "whiteSQL.hh"

	/** Default (and the only one) Constructor
         */

	 whiteSQL::SqlInitialized::SqlInitialized()
	 {
	   mysql = mysql_init(NULL);
	 }



	/** Get the pointer to the MySQL initialized structure
	 *  @return   The MySQL initialized structure
         */

	 MYSQL* whiteSQL::SqlInitialized::Get()
	 { 
	   return mysql;
	 }

	/** tests if the MySQL pointer it's NULL
	 *  @return   true if it's null other wise false.
         */

	 bool whiteSQL::SqlInitialized::isNull()
	 {
 	    if( NULL == mysql )
		return true;

	  return false;
	 }

	 /** Appends (and replace) the MySQL initialized struct
	  */
	 void whiteSQL::SqlInitialized::operator << (MYSQL *mysql){}
	
