#include "SQLResult.hh"





  std::string whsql::SQLResult::getValue(int row, int col )
  {
        return m_array[col][row];
  }

  void whsql::SQLResult::removeValue(int row, int col)
  {
        m_array[col].removeValue(row);
  }

  void whsql::SQLResult::setAffected(int affected)
  {
      m_affect = affected;
  }


  int whsql::SQLResult::getAffected()
  {
    return m_affect;
  }


  int whsql::SQLResult::getColCount()
  {
        return m_array.size();
  }

  int whsql::SQLResult::getRowCount()
  {
        if( m_array.size() > 0)
            return m_array[0].getFieldCount();
    return 0;
  }


  whsql::SQLResultCol& whsql::SQLResult::operator[] (int index)
  {
      return m_array[index];
  }

  whsql::SQLResultCol& whsql::SQLResult::operator[] (std::string name)
  {
        std::vector<whsql::SQLResultCol>::iterator iter = m_array.begin();

            do
            {
                if( (*iter).getName() == name)
                    return (*iter);

            }while(iter != m_array.end());
  }


  void whsql::SQLResult::operator<< (whsql::SQLResultCol col)
  {
         m_array.push_back(col);
  }

  void whsql::SQLResult::operator<< (whsql::SQLResultRow row)
  {

            if( m_array.size() < 1)
                for( int x=0; x != row.getFieldCount(); x++)
                    m_array.push_back( whsql::SQLResultCol() );

            std::vector<whsql::SQLResultCol>::iterator iter = m_array.begin();

            for(int x=0; iter != m_array.end(); iter++, x++)
                (*iter).insertValue( row[x]);
  }
