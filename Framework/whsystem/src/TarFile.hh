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

#ifndef _TAR_FILE_
#define _TAR_FILE_


#include "WhiteHawkSystem.hh"
#include "TarResource.hh"
#include <string>
#include <libtar.h>

class WhiteHawkSystem::TarFile
{
public:

    TarFile(std::string path);


	/* recomended strip the initial '/'
	 */
	WhiteHawkSystem::TarResource* getResource(std::string name);

	WhiteHawkSystem::TarResource* getNextResource();


    bool append(std::string path,std::string savedName = "");

    bool append(WhiteHawkSystem::FileInfo *file,std::string savedName = "");

    bool appendTree( std::string path,std::string savedName = "");

    bool appendTree(WhiteHawkSystem::SystemPath *path, std::string savedName = "");

	bool extractResource(std::string name, std::string path );

	bool extractResource(WhiteHawkSystem::TarResource *resource, std::string path );

    bool extractAll(std::string path);

    bool close();


protected:
TAR *dir;
std::string path;
};
#endif
