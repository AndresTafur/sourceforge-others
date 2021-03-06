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


#ifndef _SYSTEMPATH_COUNT_
#define _SYSTEMPATH_COUNT_

#include "WhiteHawkUtil.hh"
#include "AbstractFile.hh"

/**
 *  This class encapsulates two counted data from a SystemPath.
 */

class WhiteHawkUtil::SystemPathCount
{
public:
            /**
             *  Default constructor.
             *  @param files  Total amount of files.
             *  @param folders Total amount folders including '.' and '..'.
             *  @param links Total amount of links.
             *  @param dev Total amount of devices.
             */
            SystemPathCount(unsigned long long files = 0, unsigned long long folders = 0, unsigned long long links = 0, unsigned long long fifo = 0, unsigned long long blkdev = 0, unsigned long long chardev = 0);


            /**
             *  Sets the total amount of files.
             *  @param count Amount of files.
             */
            void setFilesCount(unsigned long long count);


            /**
             *  Sets total amount of folders, including '.' and '..' (when comes from SystemPath).
             *  @param count total amount of folders.
             */
            void setFoldersCount(unsigned long long count);


            /**
             *  Sets total amount of soft links.
             *  @param count total amount of links.
             */
            void setLinksCount(unsigned long long count);


            /**
             *  Sets total amount of fifo files.
             *  @param count total amount of fifo.
             */
            void setFIFOCount(unsigned long long count);

            /**
             *  Sets total amount of special char devices.
             *  @param count total amount of char devices.
             */
            void setCharDevicesCount(unsigned long long count);


            /**
             *  Sets total amount of special block devices.
             *  @param count total amount of block devices.
             */
            void setBlockDevicesCount(unsigned long long count);

            /**
             *  Returns total amount of files.
             *  @return total amount of files.
             */
            unsigned long long getFilesCount();


            /**
             *  Returns total amount of folders, including '.' and '..' (when comes from SystemPath).
             *  @return total amount of folders.
             */
            unsigned long long getFoldersCount();


            /**
             *  Returns total amount of soft links.
             *  @return total amount of links.
             */
            unsigned long long getLinksCount();


            /**
             *  Returns total amount of FIFO counts.
             *  @return total amount of FIFO files.
             */
            unsigned long long getFIFOCount();

            /**
             *  Returns total amount of special devices (char and block).
             *  @return total amount of devices.
             */
            unsigned long long getDevicesCount();

            /**
             *  Returns total amount of special char devices.
             *  @return total amount of char devices.
             */
            unsigned long long getCharDevicesCount();

            /**
             *  Returns total amount of special block devices.
             *  @return total amount of block devices.
             */
            unsigned long long getBlockDevicesCount();

            /**
             *  Returns total amount of files including regular,folders,devices,and soft-links.
             *  @return total amount of files, including '.' and '..' (when comes from SystemPath).
             */
            unsigned long long getTotalCount();


            /**
             * Adds a file to the amount by testing its type.
             * @param obj file to be added
             */

            void operator += (WhiteHawkUtil::FileInfo obj);

            /**
             * Removes a file to the amount by testing its type.
             * @param obj file to be removed
             */
            void operator -= (WhiteHawkUtil::FileInfo obj);


            /**
             * Adds another filecount to the amount.
             * @param obj Count to be added
             */
            void operator += (WhiteHawkUtil::SystemPathCount obj);


            /**
             * Removes another filecount to the amount.
             * @param obj Count to be removed
             */
            void operator -= (WhiteHawkUtil::SystemPathCount obj);

protected:

/**
 * Total amount of files.
 */
unsigned long long m_files;

/**
 * Total amount of folders.
 */
unsigned long long m_folders;

/**
 * Total amount of devices.
 */
unsigned long long m_chardev;

/**
 * Total amount of devices.
 */
unsigned long long m_blkdev;

/**
 * Total amount of devices.
 */
unsigned long long m_fifo;

/**
 * Total amount of links.
 */
unsigned long long m_link;

};

#endif
