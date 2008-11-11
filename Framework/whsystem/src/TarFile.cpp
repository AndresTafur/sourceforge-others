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

#include "TarFile.hh"
#include "Exception.hh"
#include "FileInfo.hh"
#include "SystemPath.hh"
#include <stdlib.h>
#include <fcntl.h>



    WhiteHawkSystem::TarFile::TarFile(std::string path)
    {
        tar_open(&m_handler,(char*)path.c_str(),NULL,O_RDONLY,0,0);
    }

    WhiteHawkSystem::TarResource*  WhiteHawkSystem::TarFile::getResource(std::string name)
    {
      WhiteHawkSystem::TarResource *tmp;

        do
        {
           tmp = getNextResource();

            if(!tmp)
              return NULL;

            if( tmp->getName().compare(name) != 0)
              return tmp;

            free(tmp);

        }while(true);
    }

    WhiteHawkSystem::TarResource* WhiteHawkSystem::TarFile::getNextResource()
    {
        if( th_read(m_handler) == -1)
            return NULL;

        return (new WhiteHawkSystem::TarResource(m_handler));
    }


    bool WhiteHawkSystem::TarFile::append(std::string path, std::string savedName)
    {
        if( savedName.empty())
                savedName = path;
        if( tar_append_file(m_handler, (char*)path.c_str(),(char*) savedName.c_str()) != 0)
                throw (Exception("Failed adding file.","WhiteHawkSystem::TarFile::append"));

        return tar_append_eof(m_handler) == 0;
    }

    bool WhiteHawkSystem::TarFile::append(WhiteHawkSystem::FileInfo *file, std::string savedName)
    {
        if( savedName.empty())
                savedName = file->getPath();
        if( tar_append_file(m_handler,(char*) file->getPath().c_str(), (char*)savedName.c_str()) != 0)
                throw Exception("Failed adding file.","WhiteHawkSystem::TarFile::append");

        return tar_append_eof(m_handler) == 0;
    }


    bool  WhiteHawkSystem::TarFile::appendTree( std::string path,std::string savedName)
    {
        return tar_append_tree(m_handler,(char*)path.c_str(),(char*) savedName.c_str()) == 0;
    }

    bool  WhiteHawkSystem::TarFile::appendTree(WhiteHawkSystem::SystemPath *path, std::string savedName)
    {
        return tar_append_tree(m_handler, (char*)path->getPath().c_str(),(char*) savedName.c_str()) == 0;
    }


    bool WhiteHawkSystem::TarFile::extractResource(TarResource *resource, std::string path )
	{
		return resource->extract(path);
	}


    bool WhiteHawkSystem::TarFile::extractAll(std::string path)
    {
        WhiteHawkSystem::TarResource *res = getNextResource();

            if( path.at( path.length()-1 ) != '/')
                path.append(1,'/');


            while( res != NULL)
            {
                res->extract(path);
                free(res);
                res = getNextResource();
            }

            free(res);
    }

    bool WhiteHawkSystem::TarFile::close()
	{
		return tar_close(m_handler) == 0;
	}
