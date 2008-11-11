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

    /**
     *  Constructs a tar file object
     *  @param path Filesystem path to the tar archiever.
     */
    TarFile(std::string path);


	/**
	 * Obtains a file/folder within a tar archiever.
	 * @param name Name of the resource.
	 * @return File/Folder TarResource.
	 */
	WhiteHawkSystem::TarResource* getResource(std::string name);

    /**
     *  Obtains the resource at the current offset and increments it.
     *  @return next File/Folder TarResource.
     */
	WhiteHawkSystem::TarResource* getNextResource();

    /**
     *  Appends a file and optionally sets its name
     *  @param path Path to the file to be included.
     *  @param savedName Name to be included as filename into the tarball.
     *  @return true if it was added, false otherwise.
     */
    bool append(std::string path,std::string savedName = "");

    /**
     *  Appends a file and optionally sets its name
     *  @param file file to be included.
     *  @param savedName Name to be included as filename into the tarball.
     *  @return true if it was added, false otherwise.
     */
    bool append(WhiteHawkSystem::FileInfo *file,std::string savedName = "");

    /**
     *  Appends a complete path and optionally sets its name
     *  @param path Path to be included (must be a directory).
     *  @param savedName Name to be included as dirname into the tarball.
     *  @return true if it was added, false otherwise.
     */
    bool appendTree( std::string path,std::string savedName = "");

    /**
     *  Appends a complete path and optionally sets its name
     *  @param path Path to be included (must be a directory).
     *  @param savedName Name to be included as dirname into the tarball.
     *  @return true if it was added, false otherwise.
     */
    bool appendTree(WhiteHawkSystem::SystemPath *path, std::string savedName = "");

    /**
     *  Extracts a resource into a path.
     *  @param name Name of the resource to be extracted.
     *  @param path Filesystem path wheter extract the resource.
     *  @return true if extracted, false otherwise.
     */
	bool extractResource(std::string name, std::string path );

    /**
     *  Extracts a resource into a path.
     *  @param name Resource to be extracted.
     *  @param path Filesystem path wheter extract the resource.
     *  @return true if extracted, false otherwise.
     */
	bool extractResource(WhiteHawkSystem::TarResource *resource, std::string path );

    /**
     *  Extracts all resources into a path.
     *  @param path Filesystem path wheter extract the resource.
     *  @return true if extracted, false otherwise.
     */
    bool extractAll(std::string path);

    /**
     *  Close the current tarball.
     *  @return true if closed, false otherwise.
     */
    bool close();


protected:
/**
 * Tar handler.
 */
TAR *m_handler;
};
#endif
