#ifndef _SYSTEMPATH_COUNT_
#define _SYSTEMPATH_COUNT_

#include "WhiteHawkSystem.hh"


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
            SystemPathCount(unsigned long long files = 0, unsigned long long folders = 0, unsigned long long links = 0 , unsigned long long dev = 0);


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
             *  Returns total amount of special devices.
             *  @return total amount of devices.
             */
            unsigned long long getDevicesCount();


            /**
             *  Returns total amount of files including regular,folders,devices,and soft-links.
             *  @return total amount of files, including '.' and '..' (when comes from SystemPath).
             */
            unsigned long long getTotal();

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
long long m_dev;

/**
 * Total amount of links.
 */
long long m_link;

};

#endif
