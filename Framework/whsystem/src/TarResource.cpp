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
		m_reg     = TH_ISREG(handler);
        m_dir     = TH_ISDIR(handler);
        m_link    = TH_ISLNK(handler);
        m_sym     = TH_ISSYM(handler);
        m_blck    = TH_ISBLK(handler);
        m_chr     = TH_ISCHR(handler);
        m_fifo    = TH_ISFIFO(handler);
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
        return m_reg;
	}

    bool WhiteHawkSystem::TarResource::isHardLink()
	{
        return m_link;
	}

	bool WhiteHawkSystem::TarResource::isSoftLink()
	{
        return m_sym;
	}

	bool WhiteHawkSystem::TarResource::isLink()
	{
        return m_link || m_sym;
	}

	bool WhiteHawkSystem::TarResource::isDirectory()
	{
        return m_dir;
	}

	bool WhiteHawkSystem::TarResource::isCharDevice()
	{
        return m_chr;
	}

	bool WhiteHawkSystem::TarResource::isBlockDevice()
	{
        return m_blck;
	}

	bool WhiteHawkSystem::TarResource::isFIFO()
	{
        return m_fifo;
	}

	bool WhiteHawkSystem::TarResource::isDevice()
	{
        return m_chr || m_blck;
	}

