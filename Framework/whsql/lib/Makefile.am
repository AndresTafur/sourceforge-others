lib_LTLIBRARIES = libwhsql.la
library_includedir=$(includedir)/whiteHawk/sql
library_include_HEADERS = *.hh

INCLUDES = -I/usr/local/include/sqlitle3/  
libwhsql_la_SOURCES = SQLiteSession.cpp SQLResult.cpp
libwhsql_la_LDFLAGS = -lsqlite3 -L/usr/local/lib/
