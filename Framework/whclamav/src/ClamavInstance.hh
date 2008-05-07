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
	bool loadDatabase();

	/**
	 *   Scan a file (it doesn't scan a folder path)
	 *   @param  file File to be scanned;
	 *   @return true if success otherwise false
     */
	bool scanFile(ClamFile file);

	/**
	 *   Sets the default event listener
	 *   @param listener The ClamavEvtListener listener pointer
     */
	void setListener(ClamavEvtListener *listener);

	/**
	 *  This method returns the age (in days of the database)
	 *  @return Days from the last virus database update.
	 */
	bool isDBLoaded();

	/**
	 *  This method frees all memory used by libclamav
	 */
	void destroy();

protected:

/**
 *  Pointer to a event listener
 */
ClamavEvtListener *listener;

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

/**
 *  Clamav database structure
 */
bool dbLoaded;

};
#endif
