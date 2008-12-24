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

#ifndef _CLAMAVLISTANER_
#define _CLAMAVLISTANER_

#include "WhiteHawkClamav.hh"
#include "ClamFile.hh"


/**
 *  This is an abstract class (interface) which defines de default event methods
 *  Note that all of this abstract methods will be called in a separate thread
 */

class WhiteHawkClamav::ClamavEvtListener
{
public:


	/**
	 *  This method is called for the Clamav-instance when a file is starting to be scanned
	 *  @param file	File being scanned.
	 */
	virtual void onScan(ClamFile &file, long long total) = 0;

	/**
	 *  This method is called for the Clamav-instance when a virus is found
	 *  @param file File with virus.
	 */
	virtual void onVirus(ClamFile &file) = 0;

	/**
	 *  This method is called when an error ocurrs
	 *  @param file File scanned when the error ocurred
	 *  @param errtype Message with the error description
	 */
	virtual void onError(ClamFile &file,std::string errtype ) = 0;

	/**
	 *   This method is called when all files were scanned
	 */
	virtual void onFinish() = 0;


    inline virtual ~ClamavEvtListener() { };

};
#endif
