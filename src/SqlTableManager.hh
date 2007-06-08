
/** This class represents and manipulates one table
 *  on the MySQL Database
 */



class whiteSQL::SqlTableManager
{
public:

	/** Default (and the only one) Constructor
	 *  @param table  the mysql table name
	 *  @param evt    Error and Event Manager (Abstract class)
	 *  @param init   The initialized object
	 *  @see   whiteSQL::SqlEngineEvent
	 *  @see   whiteSQL::SqlInitialized
	 *  @see   whiteSQL::SqlResult
         */

SqlTableManager(std::string table,whiteSQL::SqlEngineEvent *evt,whiteSQL::SqlInitialized *init);

	/** Gets the columns in the table
	 *
	 *  @return whiteSQL::SqlResult*  The result of the query
	 *  @see    whiteSQL::SqlResult
         */


	SqlResult* ShowColumns();



	/** Gets all of the items in the table
         *
	 *  @return whiteSQL::SqlResult*  The result of the query
	 *  @see    whiteSQL::SqlResult
         */

	SqlResult* ShowItems();


	/** Gets an specified item based on the value of a specific field
	 *
	 *  @param  field                  Specific field that identify the item
	 *  @param  type                   value of the field for the search
	 *  @return whiteSQL::SqlResult*  The result of the query
	 *  @see    whiteSQL::SqlResult
         */

	SqlResult* ShowItems(std::string field, std::string type);


	/** Gets an specified item based on his content in a specific field 
	 *
	 *  @param  field                  Specific field that identify the item
	 *  @param  type                   value of the field for the content search
	 *  @return whiteSQL::SqlResult*  The result of the query
	 *  @see    whiteSQL::SqlResult
         */

	SqlResult* ShowItemsWith(std::string field, std::string type);


	/** Gets an specified item based on his starting content in a specific field 
	 *
	 *  @param  field                  Specific field that identify the item
	 *  @param  type                   value of the field for the content search
	 *  @return whiteSQL::SqlResult*  The result of the query
	 *  @see    whiteSQL::SqlResult
         */

	SqlResult* ShowItemsStartsWith(std::string field, std::string type);


	/** Gets an specified item based on his ending content in a specific field 
	 *
	 *  @param  field                  Specific field that identify the item
	 *  @param  type                   value of the field for the content search
	 *  @return whiteSQL::SqlResult*  The result of the query
	 *  @see    whiteSQL::SqlResult
         */

	SqlResult* ShowItemsEndsWith(std::string field, std::string type);


	/** Inserts an item into the current table
	 *  if an error ocurr's the event manager will be notified
	 *
	 *  @param  vals		How many values it will have
	 *  @param  val1                the first value (it's required at least one)
	 *  @param  ... 		Another possible values
	 *  @return void		Modify the table and
	 *  @see    whiteSQL::SqlResult
         */

	void InsertInto( int vals, std::string val1, ...);


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

	void ChageValue( int col, std::string val, int col2, std::string val2 );



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

	void ChageValue( std::string col, std::string val, std::string col2, std::string val2 );


	/** Deletes an item, identified by one value
	 *  if an error ocurr's the event manager will be notified
	 *
	 *  @param  col		       FieldName wich search for
	 *  @param  val                Value in the field with search for
         */

	void DeleteFrom(std::string col, std::string val);


	/** Deletes an item, identified by one value
	 *  if an error ocurr's the event manager will be notified
	 *
	 *  @param  col		       FieldNumber wich search for
	 *  @param  val                Value in the field with search for
         */

	void DeleteFrom(int col, std::string val);


private:
 SqlInitialized *init;
 SqlEngineEvent *evt;
 SqlEngine      *eng;
 std::string    table;
};
