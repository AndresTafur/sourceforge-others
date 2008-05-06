#include "SQLiteSession.hh"

whSQL::SQLiteSession::SQLiteSession()
{}

whSQL::SQLiteSession::SQLiteSession(std::string file)
{
          sqlite3_open(file.c_str(), &m_db);
}

void whSQL::SQLiteSession::open(std::string file)
{
	sqlite3_open(file.c_str(),&m_db);
}

void whSQL::SQLiteSession::insertResult(SQLResult res)
{
    results.push_back(res);
}

whSQL::SQLResult whSQL::SQLiteSession::getResultAt(int index)
{
  std::list<whSQL::SQLResult>::iterator iter;

    if( index == 0)
        iter = results.begin();
    else if( index == (results.size()-1))
        iter = results.end();
    else
    {
        iter= results.begin();
        for(int i=0; i < index; i++, ++iter);
    }

    return (*iter);
}

std::list<whSQL::SQLResult> whSQL::SQLiteSession::getResults()
{
     return results;
}



void whSQL::SQLiteSession::ereaseValueAt(int index)
{
    if( index == 0)
        results.pop_front();
    else if( index == (results.size()-1))
        results.pop_back();
    else
    {
        std::list<whSQL::SQLResult>::iterator iter = results.begin();

        for(int i=0; i < index; i++, iter++);
        results.erase(iter);
    }

}

void whSQL::SQLiteSession::ereaseAll()
{
    results.clear();
}

bool whSQL::SQLiteSession::close()
{
    return sqlite3_close(m_db) == 0;

}

void whSQL::SQLiteSession::operator<<(std::string query)
{
    if( results.size() > 0)
        results.clear();
    sqlite3_exec(m_db,query.c_str(),whSQL::SQLiteSession::callback,this,NULL);
}



int whSQL::SQLiteSession::callback(void* session, int cols,char** value,char** err)
{
    SQLResult res;
    whSQL::SQLiteSession *ses = (whSQL::SQLiteSession*)session;

        for( int i=0; i < cols; i++)
            res.insertValue(value[i]);
        ses->insertResult(res);

return 0;
}
