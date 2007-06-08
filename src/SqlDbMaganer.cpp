#include "whiteSQL.hh"

	/** Default Constructor
	 *
	 *  @param database  the mysql database name
	 *  @param evt    Error and Event Manager (Abstract class)
	 *  @param init   The initialized object
	 *  @see   whiteSQL::SqlEngineEvent
	 *  @see   whiteSQL::SqlInitialized
	 *  @see   whiteSQL::SqlResult
     */

	whiteSQL::SqlDbManager::SqlDbManager(std::string database,whiteSQL::SqlEngineEvent *evt,whiteSQL::SqlInitialized *init)
	{
		this->init = init;
		this->evt  = evt;
		this->database = database;
		eng = new SqlEngine(evt,init);
	}


	/**
	 * Selects the schema to use in the in the default database
     */

	void whiteSQL::SqlDbManager::Select()
	{
	   eng->doQuery("USE %s",database.c_str());
	}

	/**
	 * Drops (delete) the current schemas
         */

	void whiteSQL::SqlDbManager::Drop()
	{
	   eng->doQuery("DROP %s",database.c_str());
	}

	/**
	 * Shows all schemas in the mysql
	 * @return  The result of the query
         */

	whiteSQL::SqlResult* whiteSQL::SqlDbManager::ShowDataBases()
	{
		return eng->doQuery("SHOW DATABASES");
	}


	/**
	 * Shows all schemas that contents 'like' in they name
	 *
	 * @param   like  The string for the search
	 * @return  The result of the query
         */

	whiteSQL::SqlResult* whiteSQL::SqlDbManager::ShowDataBasesWith(std::string like)
	{
		return eng->doQuery("SHOW DATABASES LIKE '%%s%'",like.c_str());
	}


	/**
	 * Shows all schemas that stars with 'like' in they name
	 *
	 * @param   like  The string for the search
	 * @return  The result of the query
         */

	whiteSQL::SqlResult* whiteSQL::SqlDbManager::ShowDataBasesStartWith(std::string like)
	{
		return eng->doQuery("SHOW DATABASES LIKE '%s%'",like.c_str());
	}


	/**
	 * Shows all schemas that ends with 'like' in they name
	 *
	 * @param   like  The string for the search
	 * @return  The result of the query
         */

	whiteSQL::SqlResult* whiteSQL::SqlDbManager::ShowDataBasesEndWith(std::string like)
	{
		return eng->doQuery("SHOW DATABASES LIKE '%%s'",like.c_str());
	}


	/**
	 * Shows all the tables in the current schema
	 *
	 * @return  The result of the query
         */

	whiteSQL::SqlResult* whiteSQL::SqlDbManager::ShowTables()
	{
		return eng->doQuery("SHOW TABLES");
	}

	/**
	 * Shows all the tables in the current schema that matches with the param
	 *
	 * @param  like  The searched name of table
 	 * @return  The result of the query
         */

	whiteSQL::SqlResult* whiteSQL::SqlDbManager::ShowTablesWith(std::string like)
	{
		return eng->doQuery("SHOW TABLES LIKE '%s'",like.c_str());
	}



	/**
	 * Shows all the tables in the current schema that starts with one expression
	 *
	 * @param    like    Expression to match starting.
	 * @return  The result of the query
         */

	whiteSQL::SqlResult* whiteSQL::SqlDbManager::ShowTablesStarsWith(std::string like)
	{
		return eng->doQuery("SHOW TABLES LIKE '%s%'",like.c_str());
	}


	/**
	 * Shows all the tables in the current schema that starts with one expression
	 *
	 * @param    like    Expression to match ending.
	 * @return  The result of the query
         */

	whiteSQL::SqlResult* whiteSQL::SqlDbManager::ShowTablesEndsWith(std::string like)
	{
		return eng->doQuery("SHOW TABLES LIKE '%%s'",like.c_str());
	}
