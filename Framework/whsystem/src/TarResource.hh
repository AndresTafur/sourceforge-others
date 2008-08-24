

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

	bool isFile();

    bool isHardLink();

    bool isSoftLink();

	bool isLink();

	bool isDirectory();

	bool isCharDevice();

	bool isBlockDevice();

	bool isFIFO();

	bool isDevice();


protected:
TAR *m_handler;
std::string m_name;
bool m_eof;
bool m_reg;
bool m_dir;
bool m_link;
bool m_sym;
bool m_blck;
bool m_chr;
bool m_fifo;
};
#endif
