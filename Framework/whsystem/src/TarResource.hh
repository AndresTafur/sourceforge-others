/*  This file is part of WhiteHawkClamav.

    WhiteHawkClamav is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WhiteHawkClamav is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with WhiteHawkClamav.  If not, see <http://www.gnu.org/licenses/>.
*/

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
