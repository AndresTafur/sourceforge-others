
/**
 *  This class initiates the MySQL struct
 */


class whiteSQL::SqlInitialized
{
public:


	/** Default (and the only one) Constructor
         */

	 SqlInitialized();



	/** Get the pointer to the MySQL initialized structure
	 *  @return   The MySQL initialized structure
         */

	 MYSQL* Get();


	/** tests if the MySQL pointer it's NULL
	 *  @return   true if it's null other wise false.
         */

	 bool isNull();


	 /** Appends (and replace) the MySQL initialized struct
	  */

	 void operator << (MYSQL *mysql);

protected:
/** Pointer to MySQL struct
 */
MYSQL *mysql;

};
