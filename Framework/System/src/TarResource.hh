

#ifndef _TAR_RESOURCE_
#define _TAR_RESOURCE_

#include <libtar.h>
#include <dirent.h>
#include <iostream>

#include "WhiteHawkSystem.hh"


class WhiteHawkSystem::TarResource
{
public:

	TarResource(TAR *handler);


	void setName(std::string name);


	std::string getName();


	std::string getContent();


	bool extract();


    bool extract(std::string path);


	bool isOpen();

	bool isEof();

	void rewind();

	void close();


protected:
TAR *handler;
std::string name;
bool eof;
};
#endif
