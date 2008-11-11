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

#include "TarResource.hh"
#include "SystemPath.hh"
#include <string.h>


	WhiteHawkSystem::TarResource::TarResource(TAR *handler)
	{
		m_eof = false;
		m_handler = handler;
		m_name    = th_get_pathname(handler);
	}


	void WhiteHawkSystem::TarResource::setName(std::string name)
	{
		this->m_name = name;
	}


	std::string WhiteHawkSystem::TarResource::getName()
	{
		return m_name;
	}


	std::string WhiteHawkSystem::TarResource::getContent()
	{
	   char buf[T_BLOCKSIZE];
	   int   i,k;
	   std::string str;

	        for (i = th_get_size(m_handler); i > 0; i -= T_BLOCKSIZE)
            {
                k = tar_block_read(m_handler, buf);
                if (k != T_BLOCKSIZE)
                  break;
            }

            str = buf;

	    return str;
	}


	bool WhiteHawkSystem::TarResource::extract()
	{
	     return  tar_extract_file(m_handler,(char*)m_name.c_str()) == 0;
	}


    bool WhiteHawkSystem::TarResource::extract(std::string path)
	{
        FILE *fdout;
        int i, k;
        char buf[T_BLOCKSIZE];

            if( path.at(path.length()) != '/')
                path += '/';

            WhiteHawkSystem::SystemPath::mkdirhier(path.c_str());

            path += th_get_pathname(m_handler);

            fdout = fopen(path.c_str(),"ab");

			fprintf(fdout, getContent().c_str());

            fclose(fdout);

        return true;
	}


	bool WhiteHawkSystem::TarResource::isOpen()
	{
		if(m_handler)
		  return true;
	   return false;
	}

	bool WhiteHawkSystem::TarResource::isEof()
	{
	  return m_eof;
	}


	bool WhiteHawkSystem::TarResource::isFile()
	{
        return TH_ISREG(m_handler);
	}

    bool WhiteHawkSystem::TarResource::isHardLink()
	{
        return TH_ISLNK(m_handler);
	}

	bool WhiteHawkSystem::TarResource::isSoftLink()
	{



        return TH_ISSYM(m_handler);
	}

	bool WhiteHawkSystem::TarResource::isLink()
	{
        return TH_ISLNK(m_handler) || TH_ISSYM(m_handler);
	}

	bool WhiteHawkSystem::TarResource::isDirectory()
	{
        return TH_ISDIR(m_handler);
	}

	bool WhiteHawkSystem::TarResource::isCharDevice()
	{
        return TH_ISCHR(m_handler);
	}

	bool WhiteHawkSystem::TarResource::isBlockDevice()
	{
        return TH_ISBLK(m_handler);
	}

	bool WhiteHawkSystem::TarResource::isFIFO()
	{
        return TH_ISFIFO(m_handler);
	}

	bool WhiteHawkSystem::TarResource::isDevice()
	{
        return TH_ISCHR(m_handler) || TH_ISBLK(m_handler);
	}

