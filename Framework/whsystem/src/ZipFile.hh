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

#ifndef _ZIP_FILE_
#define _ZIP_FILE_

#include "ZipResource.hh"

//TODO: Compression

class WhiteHawkSystem::ZipFile
{
public:


	ZipFile(std::string path);


	/* recomended strip the initial '/'
	 */
	WhiteHawkSystem::ZipResource*  getResource(std::string name);

	WhiteHawkSystem::ZipResource* getNextResource();


	bool extractResource(std::string name, std::string path );


	bool extractResource(WhiteHawkSystem::ZipResource *resource, std::string path );


    bool extractAll(std::string path);


	bool isOpen();


	bool close();

    ~ZipFile();

protected:
ZZIP_DIR* dir;

};
#endif
