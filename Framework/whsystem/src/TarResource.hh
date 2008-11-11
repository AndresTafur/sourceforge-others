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

    /**
     * Constructs a tar resource based on the current tarball offset.
     *  @param handler tarball handler.
     */
	TarResource(TAR *handler);

    /**
     *  Sets the tarball resource name.
     *  @param name Name to be set.
     */
	void setName(std::string name);

    /**
     *  Gets the resource name
     *  @return current resource name.
     */
	std::string getName();

    /**
     *  Gets the resource content (in a string object).
     *  @return String with the tar resource content.
     */
	std::string getContent();

    /**
     * Extracts this resource in the current path
     * @return true if succeed, false otherwise.
     */
	bool extract();

    /**
     *  Extract this resource into a path structure
     *  @return true if sucessful, false otherwise
     */
    bool extract(std::string path);

    /**
     *  Checks if the tarball is open
     *  @return true if is open, false otherwise.
     */
	bool isOpen();

    /**
     *  Checks if the tarball is at the end of file.
     *  @return true if is open, false otherwise.
     */
	bool isEof();

    /**
     * test if this resource is a regular file
     * @return true if it is regular, false otherwise.
     */
	bool isFile();

    /**
     * test if this resource is a hard link file
     * @return true if it is hard link, false otherwise.
     */
    bool isHardLink();

    /**
     * test if this resource is a soft link file
     * @return true if it is soft link, false otherwise.
     */
    bool isSoftLink();

    /**
     * test if this resource is a either hard link or softlink file.
     * @return true if it is link, false otherwise.
     */
	bool isLink();

    /**
     * test if this resource is a directory.
     * @return true if it is directory, false otherwise.
     */
	bool isDirectory();

    /**
     * test if this resource is a char device.
     * @return true if it is a char device, false otherwise.
     */
	bool isCharDevice();

    /**
     * test if this resource is a block device.
     * @return true if it is a block device, false otherwise.
     */
	bool isBlockDevice();

    /**
     * test if this resource is a FIFO device.
     * @return true if it is a FIFO device, false otherwise.
     */
	bool isFIFO();

    /**
     * test if this resource is any device.
     * @return true if it is a device, false otherwise.
     */
	bool isDevice();


protected:
/**
 * tarbll handler
 */
TAR *m_handler;

/**
 * Resource name
 */
std::string m_name;

/**
 * if it is eof
 */
bool m_eof; //TODO: change this.
};
#endif
