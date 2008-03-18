#ifndef _SQLRESULT_ROW_
#define _SQLRESULT_ROW_

#include "WhSQL.hh"
#include <vector>
#include <string>


/**
 *  This class represents a Result row
 */

class whsql::SQLResultRow
{
public:

       /**
        * inserts a value into the row.
        * @param val Value to be inserted.
        */

        void insertValue(std::string  val);

       /**
        * inserts a value into the row.
        * @param val Value to be inserted.
        * @param index where will be inserted.
        */

        void insertValue(std::string  val, int index);

       /**
        * Removes a value into the row.
        * @param index Index of the value.
        */
        void removeValue(int index);


       /**
        * Removes values into the row.
        * @param val value to be removed.
        */
        void removeValues(std::string val);

       /**
        * Gets the amount of fields.
        * @return Total amount of fields in this row.
        */
        int getFieldCount();

       /**
        * Gets the amount of fields.
        * @param index index to be obtained.
        * @return Total amount of fields in this row.
        */
        std::string& operator[] (int  index);


       /**
        * Inserts a value into the row
        * @param str String to be inserted.
        */
        void operator << (std::string str);

protected:
/**
 * Vector of fields in the row
 */
std::vector<std::string> m_fields;

};

#endif
