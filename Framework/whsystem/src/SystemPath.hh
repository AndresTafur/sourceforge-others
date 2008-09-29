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

#ifndef _SYSTEM_PATH_
#define _SYSTEM_PATH_

#include <string>
#include <list>
#include <dirent.h>

#include "WhiteHawkSystem.hh"
#include "AbstractFile.hh"
#include "SystemPathCount.hh"

/**
 *  This class controls the access to a path (folders and subfolders)
 */

class WhiteHawkSystem::SystemPath
{
public:

        /**
         *   Default constructor.
         *   @param path Path to be constructed in memory.
         */
        SystemPath(std::string path);

        /**
         *   Gets the file count of a defined file, should be accessed in
         *   a statical way.
         *   @param file Folder to start counting.
         *   @return the number of files, folders, etc in the current folder.
         */
        static SystemPathCount getCount(AbstractFile &file);

        /**
         *   Gets the file count of a defined path, should be accessed in
         *   a statical way.
         *   @param path Path to be file counted.
         *   @return the number of files and folders in the current folder.
         */
        static SystemPathCount getCount(std::string path);


        /**
         *   Gets the file count of the current path.
         *   @return the number of files and folders in the current folder.
         */
        SystemPathCount getCount();

        /**
         *   Gets the file count of the current path.
         *   @return Path of this object.
         */
        std::string getPath();


        /**
         *   Gets the system dependent current directory, should be accessed in
         *   a statical way.
         *   @return An abstract file representing the CWD (it's a directory).
         */
        static WhiteHawkSystem::AbstractFile getCurrentWDir();


        /**
         *   Sets the system dependent current directory, should be accessed in
         *   a statical way.
         *   @param dir AbstractFile object to be set as a cwd (must be a directory).
         *   @return true if the CWD has been changed, false otherwise.
         */
        static bool setCurrentWDir(WhiteHawkSystem::AbstractFile dir);

        /**
         *   Sets the system dependent current directory, should be accessed in
         *   a statical way.
         *   @param dir Path to be set as the cwd (must be a directory).
         *   @return true if the CWD has been changed, false otherwise.
         */
        static bool setCurrentWDir(std::string dir);


        /**
         *   Tests if the offset is in the last element of the path folder.
         *   @return true if is pointing the last, false otherwise
         */
        bool isEnd();

        /**
         *  Finds a file based on the file name.
         *  @param  name File name to be searched.
         *  @return An abstract file representing the file found, an Abstract Empty file otherwise
         */
        WhiteHawkSystem::AbstractFile find(std::string name);

        /**
         *  Get's the next file in the path, and increments the offset, if there is no file
         *  it will return a file with an empty path.
         *  @return An abstract file representing the next file, it excludes '.' and '..'.
         */
        WhiteHawkSystem::AbstractFile getNextFile();

        /**
         *  Make's a dir hierarchy based on the path
         *  @param  path Absolute path to the route to be created.
         *  @return Returns 0 on success, -1 otherwise.
         */
        static int mkdirhier(const char*path);


protected:
/**
 *  Directory handler.
 */
DIR *dir;

/**
 *  File count value.
 */
int count;

/**
 *  End of file flag.
 */
bool eof;

/**
 *  Dirent pointer of the current directory.
 */
struct dirent *red;

/**
 *  Setted Path.
 */
std::string path;
};

#endif
