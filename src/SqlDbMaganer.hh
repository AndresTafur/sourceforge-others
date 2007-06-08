
/** This class Represents a Schema on the
 *  mysql database.
 */

class whiteSQL::SqlDbManager
{
public:


	/** Default Constructor
	 *
	 *  @param database  the mysql database name
	 *  @param evt    Error and Event Manager (Abstract class)
	 *  @param init   The initialized object
	 *  @see   whiteSQL::SqlEngineEvent
	 *  @see   whiteSQL::SqlInitialized
	 *  @see   whiteSQL::SqlResult
         */

SqlDbManager(std::string database,whiteSQL::SqlEngineEvent *evt,whiteSQL::SqlInitialized *init);


	/**
	 * Selects the schema to use in the in the default database
    	 */

	void Select();

	/**
	 * Drops (delete) the current schemas
         */

	void Drop();

	/**
	 * Shows all schemas in the mysql
	 * @return  The result of the query
         */

	SqlResult* ShowDataBases();

	/**
	 * Shows all schemas that contents 'like' in they name
	 *
	 * @param   like  The string for the search
	 * @return  The result of the query
         */

	SqlResult* ShowDataBasesWith(std::string like);

	/**
	 * Shows all schemas that stars with 'like' in they name
	 *
	 * @param   like  The string for the search
	 * @return  The result of the query
         */

	SqlResult* ShowDataBasesStartWith(std::string like);


	/**
	 * Shows all schemas that ends with 'like' in they name
	 *
	 * @param   like  The string for the search
	 * @return  The result of the query
         */

	SqlResult* ShowDataBasesEndWith(std::string like);

	/**
	 * Shows all the tables in the current schema
	 *
	 * @return  The result of the query
         */

	SqlResult* ShowTables();

	/**
	 * Shows all the tables in the current schema that matches with the param
	 *
	 * @param  like  The searched name of table
 	 * @return  The result of the query
         */

	SqlResult* ShowTablesWith(std::string like);


	/**
	 * Shows all the tables in the current schema that starts with one expression
	 *
	 * @param    like    Expression to match starting.
	 * @return  The result of the query
         */

	SqlResult* ShowTablesStarsWith(std::string like);


	/**
	 * Shows all the tables in the current schema that starts with one expression
	 *
	 * @param    like    Expression to match ending.
	 * @return  The result of the query
         */

	SqlResult* ShowTablesEndsWith(std::string like);

protected:

 /** Pointer to the whiteSQL::SqlInitialized class
  */
 SqlInitialized *init;

 /** Pointer to the Event manager
  */
 SqlEngineEvent *evt;

 /** Pointer to the whiteSQL::SQLEngine object
  */
 SqlEngine      *eng;

 /** String  of the database name
  */
 std::string database;
};
