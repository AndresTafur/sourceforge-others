#ifndef _RESULT_ROW_H_
#define _RESULT_ROW_H_

#include <map>
#include <string>

class ResultRow
{
public:


    void addResult(std::string col, std::string val);

    std::string operator [](std::string col);

private:
std::map<std::string,std::string> m_list;
};

#endif
