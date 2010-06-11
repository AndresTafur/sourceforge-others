
#ifndef _SQL_RESULT_H_INCLUDED_
#define _SQL_RESULT_H_INCLUDED_

#include "whSQL.hh"
#include <list>
#include <string>

class whSQL::SQLResult
{
public:


        void insertValue(std::string value);

        int getColumns();

        std::list<std::string> getValues();

        std::string getValueAt(unsigned int index);

        void ereaseValueAt(unsigned int index);

        void ereaseAll();

        inline bool empty() { return values.empty();}

protected:
std::list<std::string> values;
};
#endif
