#include "whiteSQL.hh"



    /** Default (and the only one) Constructor
     *  @param res    Result of the MySQL query
     */

     whiteSQL::SqlResult::SqlResult(MYSQL_RES *res)
     {
       	   this->res = res;
	   numrow    = mysql_num_rows(res);
	   numfields = mysql_num_fields(res);
	   rows      = new MYSQL_ROW[numrow];

	   for(int i=0; i < numrow; i++)
		rows[i] = mysql_fetch_row(res);

     }


    /**
     *   Test's if the result is empty
     *   @return true if it's empty otherwise false
     */

     bool whiteSQL::SqlResult::isEmpty()
     {
            for(int j=0; j < numrow; j++)
                for(int i=0; i < numfields; i++ )
                    if( rows[j][i] != NULL || strlen(rows[j][i]) != 0)
                   		return false;

            return true;
     }

    /**
     *  Search's for a string and returns
     *  the row, field and string of the
     *  specific cell
     *
     *  @return The row, field and content managed by ResultContent
     *  @see    ResultContent
     */

     whiteSQL::ResultContent* whiteSQL::SqlResult::contains(std::string str)
     {

        int field;

            for(int i=0; i < numrow; i++)
            {
                field = this->getFieldOf(i,str);

                if( field )
                   return new ResultContent(i,field,str);
            }

        return NULL;
     }


   /**
     *  Search's for a string in a given row and returns
     *  the containing field
     *
     *  @param  row Row in which search for the string
     *  @param  str The searched string
     *  @return The field containing the string
     */

     int whiteSQL::SqlResult::getFieldOf(int row, std::string str)
     {
            for(int i=0; i < numfields; i++ )
                if( str.compare(this->getResultAt(row,i)) == 0 )
                    return i;

        return NULL;
     }



   /**
     *  Search's for a string in a given field and returns
     *  the containing row
     *
     *  @param  field Field in which search for the string
     *  @param  str The searched string
     *  @return The field containing the string
     */

     int whiteSQL::SqlResult::getRowOf(int field, std::string str)
     {
            for(int i=0; i < numrow; i++ )
                if( str.compare(this->getResultAt(i,field)) == 0 )
                    return i;

        return NULL;
     }


   /**
     *  Test's if a string is in a specific row
     *
     *  @param  row Row in which search for the string
     *  @param  str The searched string
     *  @return True if the row contains the string otherwise false
     */

    bool whiteSQL::SqlResult::containsInRow(int row, std::string str)
    {
        if( ! this->getFieldOf(row, str) )
            return false;
      return true;
    }


   /**
     *  Test's if a string is in a specific field
     *
     *  @param  field Field in which search for the string
     *  @param  str T he searched string
     *  @return True  if the row contains the string otherwise false
     */

    bool whiteSQL::SqlResult::containsInField(int field, std::string str)
    {
        if( !this->getRowOf(field, str) )
            return false;
      return true;
    }


    /**
     *   Returns the number of fields (columns) in the query
     *   @return Number of fields
     */

        int whiteSQL::SqlResult::getFields()
        {
            return numfields;
        }

    /**
     *   Returns the number of rows (columns) in the query
     *   @return Number of rows
     */

        int whiteSQL::SqlResult::getRows()
        {
            return numrow;
        }

    /**
     *   Returns the string at the (row, field)
     *   @param row   Row of the result
     *   @param field Colum of the result
     *   @return The string of the result at the row, field postion
     */
        std::string whiteSQL::SqlResult::getResultAt(int row, int field)
        {
		if( row >= numrow || field >= numfields )
			return "";
            return rows[row][field];
        }
