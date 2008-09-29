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

#include "ZipFile.hh"
#include "Exception.hh"
#include <stdlib.h>

//TODO: Compression

	WhiteHawkSystem::ZipFile::ZipFile(std::string path)
	{
 	   dir = zzip_opendir(path.c_str());
	}



	/*
	 * recomended strip the initial '/'
	 */
	WhiteHawkSystem::ZipResource*  WhiteHawkSystem::ZipFile::getResource(std::string name)
	{
		if( name.at(0) == '/')
			name =  name.substr(1, name.length());

 	  ZZIP_FILE *myfile =  zzip_file_open(dir, name.c_str(),0);
	  ZipResource *file;

		if(!myfile)
		   throw Exception("Failed obtaining resource.","WhiteHawkSystem::ZipFile::getResource");

		file = new ZipResource(myfile);
		file->setName(name);
		free(myfile);

	   return file;
	}

	WhiteHawkSystem::ZipResource* WhiteHawkSystem::ZipFile::getNextResource()
	{
	  ZZIP_DIRENT *dirent = zzip_readdir(dir);

		if( !dirent)
		 throw Exception("Failed obtaining resource.","WhiteHawkSystem::ZipFile::getNextResource");

		return getResource(dirent->d_name);

	}


	bool WhiteHawkSystem::ZipFile::extractResource(std::string name, std::string path )
	{
		return extractResource(getResource(name),path);
	}


	bool WhiteHawkSystem::ZipFile::extractResource(ZipResource *resource, std::string path )
	{
		return resource->extract(path);
	}


    bool WhiteHawkSystem::ZipFile::extractAll(std::string path)
    {
        WhiteHawkSystem::ZipResource *res = getNextResource();

            if( path.at( path.length()-1 ) != '/')
                path.append(1,'/');


            while( res != NULL)
            {
                res->extract(path);
                res = getNextResource();
            }
    }



	bool WhiteHawkSystem::ZipFile::isOpen()
	{
	   if(dir)
	     return true;

	  return false;
	}



	bool WhiteHawkSystem::ZipFile::close()
	{
	     zzip_dir_close(dir);
	    if(!dir)
		 return true;
	  return false;
	}

    WhiteHawkSystem::ZipFile::~ZipFile()
    {
        this->close();
    }
