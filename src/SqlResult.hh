/**
 *  This Class manages all of the results given by the queries
 */

class whiteSQL::SqlResult
{
 public:


    /** Default (and the only one) Constructor
     *  @param res    Result of the MySQL query
     */

     SqlResult(MYSQL_RES *res);


    /**
     *   Test's if the result is empty
     *   @return true if it's empty otherwise false
     */

     bool isEmpty();
    /**
     *  Search's for a string and returns
     *  the row, field and string of the
     *  specific cell
     *  @return The row, field and content managed by ResultContent
     *  @see    ResultContent
     */

     ResultContent* contains(std::string str);

   /**
     *  Search's for a string in a given row and returns
     *  the containing field
     *
     *  @param  row Row in which search for the string
     *  @param  str The searched string
     *  @return The field containing the string
     */

     int getFieldOf(int row, std::string str);


   /**
     *  Search's for a string in a given field and returns
     *  the containing row
     *
     *  @param  field Field in which search for the string
     *  @param  str The searched string
     *  @return The field containing the string
     */

     int getRowOf(int field, std::string str);

   /**
     *  Test's if a string is in a specific row
     *
     *  @param  row Row in which search for the string
     *  @param  str The searched string
     *  @return True if the row contains the string otherwise false
     */

    bool containsInRow(int row, std::string str);


   /**
     *  Test's if a string is in a specific field
     *
     *  @param  field Field in which search for the string
     *  @param  str T he searched string
     *  @return True  if the row contains the string otherwise false
     */

    bool containsInField(int field, std::string str);


    /**
     *   Returns the number of fields (columns) in the query
     *   @return Number of fields
     */

        int getFields();

    /**
     *   Returns the number of rows (columns) in the query
     *   @return Number of rows
     */

        int getRows();

    /**
     *   Returns the string at the (row, field)
     *   @param row   Row of the result
     *   @param field Colum of the result
     *   @return The string of the result at the row, field postion
     */
        std::string getResultAt(int row, int field);


protected:
 MYSQL_RES *res;
 MYSQL_ROW *rows;

 int numrow;
 int numfields;

};
