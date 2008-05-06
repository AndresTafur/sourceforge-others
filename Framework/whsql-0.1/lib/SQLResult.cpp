
#include "SQLResult.hh"


void whSQL::SQLResult::insertValue(std::string value)
{
        values.push_back(value);
}

int whSQL::SQLResult::getColumns()
{
        return values.size();
}

std::list<std::string> whSQL::SQLResult::getValues()
{
     return values;
}

std::string whSQL::SQLResult::getValueAt(int index)
{
  std::list<std::string>::iterator iter;

        if( index == 0)
            iter = values.begin();
        else
        {
            iter= values.begin();
            for(int i=0; i < index; i++, ++iter);
        }

        return (*iter);
}


void whSQL::SQLResult::ereaseValueAt(int index)
{
    if( index == 0)
        values.pop_front();
    else if( index == (values.size()-1))
        values.pop_back();
    else
    {
        std::list<std::string>::iterator iter = values.begin();

        for(int i=0; i < index; i++, iter++);
        values.erase(iter);
    }

}

void whSQL::SQLResult::ereaseAll()
{
    values.clear();
}
