#include "SQLResultRow.hh"


        void whsql::SQLResultRow::insertValue(std::string val)
        {
            m_fields.push_back(val);
        }


        void whsql::SQLResultRow::insertValue(std::string val, int index)
        {
           std::vector<std::string>::iterator iter = m_fields.begin();

            iter += index;
            m_fields.insert( iter, val );
        }


        void whsql::SQLResultRow::removeValue(int index)
        {
           std::vector<std::string>::iterator iter = m_fields.begin();

            iter += index;
            m_fields.erase(iter);
        }


        void whsql::SQLResultRow::removeValues(std::string val)
        {
            std::vector<std::string>::iterator iter = m_fields.begin();

            while( iter != m_fields.end())
            {
                if( (*iter) == val)
                {
                    m_fields.erase(iter);
                    iter = m_fields.begin();
                }
                else
                   iter++;
            }
        }


        int whsql::SQLResultRow::getFieldCount()
        {
            return m_fields.size();
        }


        std::string& whsql::SQLResultRow::operator[] (int index)
        {
            return m_fields[index];
        }


        void whsql::SQLResultRow::operator<< (std::string str)
        {
            m_fields.push_back(str);
        }

