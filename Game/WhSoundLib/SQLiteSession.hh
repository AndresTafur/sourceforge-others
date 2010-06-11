
#ifndef _SQLITLE_SESSION_H_INCLUDED_
#define _SQLITLE_SESSION_H_INCLUDED_

#include <string>
#include <list>
#include <sqlite3.h>

#include "whSQL.hh"
#include "SQLResult.hh"

class whSQL::SQLiteSession
{
public:

	SQLiteSession();

        SQLiteSession(std::string file);

        void open(std::string file);

        void insertResult(SQLResult res);

        whSQL::SQLResult getResultAt(unsigned int index);

        std::list<whSQL::SQLResult> getResults();

        void ereaseValueAt(unsigned int index);

        void ereaseAll();

        bool close();

        void doQuery( std::string query);

        void operator<< (std::string query);

        inline bool empty() { return results.empty();}

        inline int size() { return results.size(); }

protected:

        static int callback(void* session, int rows,char** value,char** err);

protected:
sqlite3 *m_db;
std::list<whSQL::SQLResult> results;
};
#endif
