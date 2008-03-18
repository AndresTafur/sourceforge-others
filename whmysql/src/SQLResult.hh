#ifndef _SQL_RESULT_
#define _SQL_RESULT_

#include "WhSQL.hh"
#include "SQLResultCol.hh"
#include "SQLResultRow.hh"

/**
 *  This class manages the rows and cols of a result
 */

class whsql::SQLResult
{
public:

        /**
         *  Get's a value based on a row and col same as [col][row]
         *  @return Field of the result.
         */

        std::string getValue(int row, int col);


        /**
         *  Removes a Field.
         *  @param row Row of the field.
         *  @param col column of the field.
         */

        void removeValue(int row, int col);

        /**
         *  Set the affected number of rows (on a update query).
         *  @param affected Number of affected rows.
         */

        void setAffected(int affected);

        /**
         *  Gets the affected number of rows (on a update query).
         *  @return Number of affected rows.
         */

        int getAffected();

        /**
         *  Gets the number of fields in the result.
         *  @return Number of fields.
         */

        int getColCount();

        /**
         *  Gets the number of rows in the result.
         *  @return Number of rows.
         */

        int getRowCount();

        /**
         *  Gets the column at the given position.
         *  @param index Index of the column
         *  @return  Columns of the result.
         */

        whsql::SQLResultCol& operator[] (int index);

        /**
         *  Gets the column with that name.
         *  @param name Name of the column.
         *  @return  Columns of the result.
         */

        whsql::SQLResultCol& operator[] (std::string name);

        /**
         *  Inserts a column to the result.
         *  @param col Column to be inserted.
         */

        void operator<< (whsql::SQLResultCol col);

        /**
         *  Inserts a row to the result.
         *  @param row Row to be inserted.
         */

        void operator<< (whsql::SQLResultRow row);


protected:

/**
 *  vector of columns.
 */
 //TODO: Change columns to rows
std::vector<whsql::SQLResultCol> m_array;

/**
 * Affected rows count.
 */
int m_affect;
};

#endif

