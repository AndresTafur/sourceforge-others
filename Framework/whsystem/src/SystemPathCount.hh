#ifndef _SYSTEMPATH_COUNT_
#define _SYSTEMPATH_COUNT_

#include "WhiteHawkSystem.hh"
#include "AbstractFile.hh"

/**
 *  This class encapsulates two counted data from a SystemPath.
 */

class WhiteHawkSystem::SystemPathCount
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
            unsigned long long getTotal();

            void operator += (WhiteHawkSystem::FileInfo obj);

            void operator -= (WhiteHawkSystem::FileInfo obj);


            void operator += (WhiteHawkSystem::SystemPathCount obj);

            void operator -= (WhiteHawkSystem::SystemPathCount obj);

protected:

/**
 * Total amount of files.
 */
long long m_files;

/**
 * Total amount of folders.
 */
long long m_folders;


/**
 * Total amount of devices.
 */
long long m_chardev;

/**
 * Total amount of devices.
 */
long long m_blkdev;

/**
 * Total amount of devices.
 */
long long m_fifo;

/**
 * Total amount of links.
 */
long long m_link;

};

#endif
