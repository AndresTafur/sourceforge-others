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


#ifndef _WH_FILE_STREAM_
#define _WH_FILE_STREAM_

#include "WhiteHawkUtil.hh"
#include "FileInfo.hh"
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/**
 *	A file data stream. This class represents a file stream based in the std::fstream
 */

class WhiteHawkUtil::AbstractFile : public  WhiteHawkUtil::FileInfo
{
public:

	/**
	 *   Constructs an empty FileInfo object.
	 */
	AbstractFile();

	/**
	 *   Constructs a FileInfo object based in a path.
	 *   @param path Route of the file.
	 */
	AbstractFile(std::string path);


    /**
	 *	Create a new Symbolic Link
	 *	@param	path	path to the new symbolic link.
	 *	@return true if sucessfull, false otherwise
	 */
    bool CreateSymLink(std::string path);


    /**
	 *	Rename this file
	 *	@param	name  new name.
	 *	@return true if sucessfull, false otherwise
	 */
    bool Rename(std::string name);


    /**
	 *	Move to new location, Note: this is equal to rename
	 *	@param	path	path to the new location.
	 *	@return true if sucessfull, false otherwise
	 */
    bool Move(std::string path);


    /**
	 *	Deletes this File (or directory)
	 *	@return true if sucessfull, false otherwise
	 */
    bool Remove();


    /**
	 *	Changes the propietary of this file
	 *  @param  user  user ID in the system.
	 *  @param  group group ID in the system.
	 *	@return true if sucessfull, false otherwise
	 */
    bool Chown(uid_t user, gid_t group);


    /**
	 *	Change the access for this file.
	 *  @param  mode  POSIX mode_t value;
	 *	@return true if sucessfull, false otherwise
	 */
    bool Chmod(mode_t mode);

    /**
	 *	Checks if the file is special.
	 *  @param  type type to be compared (ABS_DIR,ABS_FILE,ABS_DEVICE).
	 *	@return true if equals, false otherwise.
	 */
    bool operator == (short type);

   /**
	 *	Differences two object files.
	 *  @param  obj th other object to be compared.
	 *	@return true if equals, false otherwise.
	 */
    bool operator != (WhiteHawkUtil::AbstractFile obj);


public:

/**
 *  Constant to represents folders in the system.
 */
static const short ABS_DIR    = 100;

/**
 *  Constant to represents files in the system.
 */
static const short ABS_FILE   = 101;

/**
 *  Constant to represents special devices in the system.
 */
static const short ABS_DEVICE = 102;

};

#endif

