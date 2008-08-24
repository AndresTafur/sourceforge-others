#ifndef _CLAMAVINTERFACE_H
#define _CLAMAVINTERFACE_H

#include "WhiteHawkClamav.hh"
#include <clamav.h>
#include "ClamavEvtListener.hh"


/**
 *  This class is the lowlevel operation, it's used to comunicate with libclamav
 */

class WhiteHawkClamav::ClamavInstance
{
public:

	/**
	 *   loads the virus definitions database
	 *   @return true if success otherwise false
     */
	void loadDatabase();

	/**
	 *   Scan a file (it doesn't scan a folder path)
	 *   @param  file File to be scanned;
	 *   @return true if success otherwise false
     */
	bool scanFile(ClamFile &file, int total);

	/**
	 *   Adds a new event listener
	 *   @param listener The ClamavEvtListener listener pointer
     */
	void addListener(ClamavEvtListener *listener);

	/**
	 *  This method frees all memory used by libclamav
	 */
	void destroy();


    ~ClamavInstance();

protected:

/**
 *  Pointer to a event listener
 */
std::list<ClamavEvtListener*> listeners;

/**
 *  Defaul database directory
 */
const char *dbdir;

/**
 *  Clamav engine
 */
struct cl_engine *engine;

/**
 *  Clamav database structure
 */
struct cl_stat dbstat;


};
#endif
