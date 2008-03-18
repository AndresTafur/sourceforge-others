#ifndef _SQLRESULT_COL_
#define _SQLRESULT_COL_

#include "WhSQL.hh"
#include <vector>


/**
 *  This class represents a result field
 */

class whsql::SQLResultCol
{
public:

        /**
         *  Sets the name of the column.
         *  @param name Name of the column
         */
        void setName(std::string name);

        /**
         *  Inserts a value to the column.
         *  @param val Value to be inserted.
         */
        void insertValue(std::string  val);

        /**
         *  Removes a value based on the position
         *  @param index Position of the value.
         */
        void removeValue(int index);

        /**
         *  Removes all values that match the search param
         *  @param val Value to be removed, all matching fields will be removed.
         */
        void removeValues(std::string val);

        /**
         *  Count the fields of the column.
         *  @return Total fields.
         */
        int  getFieldCount();

        /**
         *  Gets the name of the column
         *  @return Name.
         */
        std::string getName();

        /**
         *  This operator returns a value based on the index
         *  @param index Index of the field.
         *  @return String value of the field.
         */
        std::string& operator[] (int  index);

        /**
         *  This operator inserts a field in this column
         *  @return String value of the field.
         */
        void operator << (std::string str);

protected:

/**
 *  Vector of fields.
 */
std::vector<std::string> m_fields;

/**
 *  Name of the current column.
 */
std::string m_colname;

};

#endif
