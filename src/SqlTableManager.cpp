#include "whiteSQL.hh"


	/** Default (and the only one) Constructor
	 *  @param table  the mysql table name
	 *  @param evt    Error and Event Manager (Abstract class)
	 *  @param init   The initialized object
	 *  @see   whiteSQL::SqlEngineEvent
	 *  @see   whiteSQL::SqlInitialized
	 *  @see   whiteSQL::SqlResult
         */

	whiteSQL::SqlTableManager::SqlTableManager(std::string table,whiteSQL::SqlEngineEvent *evt,whiteSQL::SqlInitialized *init)
	{
		this->init = init;
		this->evt  = evt;
		this->table= table;
		eng = new SqlEngine(evt,init);
	}


	/** Gets the columns in the table
	 *
	 *  @return whiteSQL::SqlResult*  The result of the query
	 *  @see    whiteSQL::SqlResult
         */


	whiteSQL::SqlResult* whiteSQL::SqlTableManager::ShowColumns()
	{
		return eng->doQuery("SHOW COLUMNS FROM %s",table.c_str());

	}



	/** Gets all of the items in the table
         *
	 *  @return whiteSQL::SqlResult*  The result of the query
	 *  @see    whiteSQL::SqlResult
         */
	whiteSQL::SqlResult* whiteSQL::SqlTableManager::ShowItems()
	{
	    return eng->doQuery("SELECT * FROM %s",table.c_str());

	}

	/** Gets an specified item based on the value of a specific field
	 *
	 *  @param  field                  Specific field that identify the item
	 *  @param  type                   value of the field for the search
	 *  @return whiteSQL::SqlResult*  The result of the query
	 *  @see    whiteSQL::SqlResult
         */
	whiteSQL::SqlResult* whiteSQL::SqlTableManager::ShowItems(std::string field, std::string type)
	{
	   return eng->doQuery("SELECT * FROM %s WHERE %s='%s'",table.c_str(),field.c_str(),type.c_str());

	}


	/** Gets an specified item based on his content in a specific field 
	 *
	 *  @param  field                  Specific field that identify the item
	 *  @param  type                   value of the field for the content search
	 *  @return whiteSQL::SqlResult*  The result of the query
	 *  @see    whiteSQL::SqlResult
         */
	whiteSQL::SqlResult* whiteSQL::SqlTableManager::ShowItemsWith(std::string field, std::string type)
	{
	    return eng->doQuery("SELECT * FROM %s WHERE %s LIKE '%%s%'",table.c_str(),field.c_str(),type.c_str());

	}


	/** Gets an specified item based on his starting content in a specific field 
	 *
	 *  @param  field                  Specific field that identify the item
	 *  @param  type                   value of the field for the content search
	 *  @return whiteSQL::SqlResult*  The result of the query
	 *  @see    whiteSQL::SqlResult
         */

	whiteSQL::SqlResult* whiteSQL::SqlTableManager::ShowItemsStartsWith(std::string field, std::string type)
	{
	    return eng->doQuery("SELECT * FROM %s WHERE %s LIKE '%s%'",table.c_str(),field.c_str(),type.c_str());

	}

	/** Gets an specified item based on his ending content in a specific field 
	 *
	 *  @param  field                  Specific field that identify the item
	 *  @param  type                   value of the field for the content search
	 *  @return whiteSQL::SqlResult*  The result of the query
	 *  @see    whiteSQL::SqlResult
         */

	whiteSQL::SqlResult* whiteSQL::SqlTableManager::ShowItemsEndsWith(std::string field, std::string type)
	{
	    return eng->doQuery("SELECT * FROM %s WHERE %s LIKE '%%s'",table.c_str(),field.c_str(),type.c_str());

	}


	/** Inserts an item into the current table
	 *  if an error ocurr's the event manager will be notified
	 *
	 *  @param  vals		How many values it will have
	 *  @param  val1                the first value (it's required at least one)
	 *  @param  ... 		Another possible values
	 *  @return void		Modify the table and
	 *  @see    whiteSQL::SqlResult
         */

	void whiteSQL::SqlTableManager::InsertInto( int vals, std::string val1, ...)
	{
	  va_list list;
	  va_start(list,val1);

	  std::string buf = "INSERT INTO " + table +" VALUES ( '" + val1 + "'";

		for( ;vals > 1;vals-- )
		{
		    buf += ",'";
		    buf.append(va_arg(list,char *));
		    buf += "'";
		}

		buf += ")";
	        eng->doQuery(buf);
	}


	/** Changes values of an item, identified by another value
	 *  if an error ocurr's the event manager will be notified
	 *
	 *  @param  col		       FieldNumber to modify (starting with 0)
	 *  @param  val                The new value
	 *  @param  col2 	       Field wich search for
	 *  @param  val2               Value in the second field with search for
	 *  @return void	       Modify the table and
	 *  @see    whiteSQL::SqlResult
         */

	void whiteSQL::SqlTableManager::ChageValue( int col, std::string val, int col2, std::string val2 )
	{
	   SqlResult *res = ShowColumns();
		
		this->ChageValue( res->getResultAt(col,0), val,res->getResultAt(col2,0) ,val2 );
	}


	/** Changes values of an item, identified by another value
	 *  if an error ocurr's the event manager will be notified
	 *
	 *  @param  col		       FieldName to modify (starting with 0)
	 *  @param  val                The new value
	 *  @param  col2 	       Field wich search for
	 *  @param  val2               Value in the second field with search for
	 *  @return void	       Modify the table and
	 *  @see    whiteSQL::SqlResult
         */

	void whiteSQL::SqlTableManager::ChageValue( std::string col, std::string val, std::string col2, std::string val2 )
	{
  
	  std::string buffer;

	  buffer = "UPDATE "+table +" SET "+ col+ "='" + val +"' WHERE " + col2 +"='" + val2 + "'";
  	  eng->doQuery(buffer);
	}


	/** Deletes an item, identified by one value
	 *  if an error ocurr's the event manager will be notified
	 *
	 *  @param  col		       FieldName wich search for
	 *  @param  val                Value in the field with search for
         */

	void whiteSQL::SqlTableManager::DeleteFrom(std::string col, std::string val)
	{
	  std::string buffer = "DELETE FROM "+ table + " WHERE "+ col + " = '"+ val +"'";
		
		std::cout << "[ " << buffer << " ]";

	    eng->doQuery(buffer);
		
	}


	/** Deletes an item, identified by one value
	 *  if an error ocurr's the event manager will be notified
	 *
	 *  @param  col		       FieldNumber wich search for
	 *  @param  val                Value in the field with search for
         */

	void whiteSQL::SqlTableManager::DeleteFrom(int col, std::string val)
	{
 	    SqlResult *res = ShowColumns();
		
		this->DeleteFrom( res->getResultAt(col,0), val );
	}
