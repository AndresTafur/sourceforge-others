lib_LTLIBRARIES = libwhclamav.la
library_includedir=$(includedir)/whiteHawk/whclamav
library_include_HEADERS = *.hh

libwhclamav_la_SOURCES = Clamav.cpp  ClamavInstance.cpp ClamFile.cpp
libwhclamav_la_CXXFLAGS = -I$(includedir)/whiteHawk/system/
libwhclamav_la_LDFLAGS = -lclamav
