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

#ifndef _CLAMAVINTERFACE_H
#define _CLAMAVINTERFACE_H

#include <clamav.h>

#include "WhiteHawkClamav.hh"
#include "ClamavEvtListener.hh"
#include "ClamavScanner.hh"


/**
 *  This class is the lowlevel operation, it's used to comunicate with libclamav
 */

class WhiteHawkClamav::ClamavInstance
{

protected:
    /**
     * Default constructor.
     */
    ClamavInstance();

public:

    static WhiteHawkClamav::ClamavInstance* getInstance();


    static WhiteHawkClamav::ClamavScanner* getScanner();

	/**
	 *   loads the virus definitions database
	 *   @return true if success otherwise false
     */
	void loadDatabase();

	/**
	 *  Checks if the database is already loaded.
	 *  @return true if loaded, false otherwise.
	 */
	 bool isDbLoaded();

     int getDatabaseAge();

    struct cl_engine* getHandler();

	/**
	 *  This method frees all memory used by libclamav
	 */
	void destroy();


    ~ClamavInstance();

protected:

/**
 * flag if db is loaded.
 */
 bool m_loaded;

/**
 *  Defaul database directory
 */
const char *m_dbdir;

/**
 *  Clamav engine
 */
struct cl_engine *m_engine;

/**
 *  Clamav database structure
 */
struct cl_stat m_dbstat;

static ClamavInstance *sm_instance;
static ClamavScanner  *sm_scanner;
friend class ClamavScanner;

};
#endif
