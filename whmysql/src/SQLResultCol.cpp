#include "SQLResultCol.hh"


        void whsql::SQLResultCol::setName(std::string name)
        {
            m_colname = name;
        }

        void whsql::SQLResultCol::insertValue(std::string val)
        {
            m_fields.push_back(val);
        }

        void whsql::SQLResultCol::removeValue(int index)
        {
           std::vector<std::string>::iterator iter = m_fields.begin();

            iter += index;
            m_fields.erase(iter);
        }


        int whsql::SQLResultCol::getFieldCount()
        {
                return m_fields.size();
        }

        void whsql::SQLResultCol::removeValues(std::string val)
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


        std::string whsql::SQLResultCol::getName()
        {
            return m_colname;
        }

        std::string& whsql::SQLResultCol::operator[] (int index)
        {
            return m_fields[index];
        }


        void whsql::SQLResultCol::operator<< (std::string str)
        {
            m_fields.push_back(str);
        }

