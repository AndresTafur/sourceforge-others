

#ifndef _ZIP_RESOURCE_
#define _ZIP_RESOURCE_

#include <zzip/lib.h>
#include <zzip/file.h>
#include <dirent.h>
#include <iostream>

#include "WhiteHawkSystem.hh"


int zzip_fstat(ZZIP_FILE* file, ZZIP_STAT* zs);

class WhiteHawkSystem::ZipResource
{
public:

	ZipResource( std::string path);

	ZipResource(ZZIP_FILE *file);


	void setName(std::string name);


	std::string getName();


	std::string getContent(int size=1);


	bool extract();


    bool extract(std::string path);


	bool isOpen();

	bool isEof();

	zzip_off_t getOffset();

	void setOffset(zzip_off_t offset, int pos = SEEK_SET);


	void rewind();


	void close();


protected:
ZZIP_FILE *handler;
std::string name;
bool eof;
};
#endif
