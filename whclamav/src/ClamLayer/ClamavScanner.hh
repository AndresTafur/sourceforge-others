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

#ifndef _CLAMAVMANAGER_H
#define _CLAMAVMANAGER_H

#include "WhiteHawkClamav.hh"
#include "ClamavInstance.hh"
#include <Thread.hh>



/**
 *  Class that manages the instance, the database and files of the Clamav antivirus
 */

class WhiteHawkClamav::ClamavScanner : public WhiteHawkSystem::Thread
{
protected:

    ClamavScanner(struct cl_engine *engine);

public:

    void scanSubFolder(ClamFile objDir);

	/**
	 *  This method runs as a thread for background scanning, should never be called directly
     */
	void run();


    void setEngine(struct cl_engine *engine);

    void setPath(std::string path);

    std::string getPath();

	/**
	 * Method that scan's the specified path
	 * @param path Path to the folder or file to be scanned.
	 */
	void startScan();

    /**
	 *   Scan a file (it doesn't scan a folder path)
	 *   @param  file File to be scanned;
	 *   @return true if success otherwise false
     */
	bool scanFile(ClamFile &file);

	/**
	 *  This method returns the total amount of files which will be scanned
	 *  @return Files in the list to be processed
     */
	long long getTotalFiles();



	/**
	 *  This method returns the age (in days of the database)
	 *  @return Days from the last virus database update.
	 */
	int getDatabaseAge();


    /**
	 *   Adds a new event listener.
	 *   @param listener The ClamavEvtListener listener pointer
     */
	void addListener(ClamavEvtListener *listener);

    /**
	 *   Removes a new event listener.
	 *   @param listener The ClamavEvtListener listener pointer
     */
	void removeListener(ClamavEvtListener *listener);



    /**
	 *  Methond called when the thread is stopped using Thread::Terminate()
	 */
	void onTerminate();


protected:

/**
 *  Clamav engine
 */
struct cl_engine *m_engine;

/**
 *  Path to the file/folder to be scanned
 */
std::string m_path;

/**
 *  Pointer to a event listener
 */
std::list<ClamavEvtListener*> m_listeners;

/**
 *  Amount of files to be scanned
 */
long long m_total;
int       m_curr;
friend class ClamavInstance;
};
#endif
