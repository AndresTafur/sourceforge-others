
#ifndef _CLAMAVMANAGER_H
#define _CLAMAVMANAGER_H

#include "WhiteHawkClamav.hh"
#include "ClamavInstance.hh"
#include <Thread.hh>



/**
 *  Class that manages the instance, the database and files of the Clamav antivirus
 */

class WhiteHawkClamav::Clamav : public WhiteHawkClamav::ClamavInstance, public WhiteHawkSystem::Thread
{
protected:

    Clamav();

public:

    static WhiteHawkClamav::Clamav* getInstance();

    void scanSubFolder(ClamFile objDir);

	/**
	 *  This method runs as a thread for background scanning, should never be called directly
     */
	void ThreadRoutine();



    void setPath(std::string path);

	/**
	 * Method that scan's the specified path
	 * @param path Path to the folder or file to be scanned.
	 */
	void startScan();

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
	 *  Methond called when the thread is stopped using Thread::Terminate()
	 */
	void onTerminate();


protected:
/**
 *  Path to the file/folder to be scanned
 */
std::string m_path;
static Clamav *m_instance;

/**
 *  Amount of files to be scanned
 */
int m_total;
int m_curr;
};
#endif
