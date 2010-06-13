#include "ResultRow.h"


    void ResultRow::addResult(std::string col, std::string val)
    {

        m_list.insert( std::make_pair(col,val)  );

    }

    std::string ResultRow::operator [](std::string col)
    {
        return m_list[col];
    }

