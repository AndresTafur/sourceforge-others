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

#include <WhiteHawkSystem.hh>
#include "WhiteHawkClamav.hh"
#include <AbstractFile.hh>
#include <SystemPath.hh>


#ifndef _CLAMFILE_HH_
#define _CLAMFILE_HH_


/**
 *  This class represents a filenode of the current path list
 */

class WhiteHawkClamav::ClamFile : public WhiteHawkSystem::AbstractFile
{
public:

	/**
	 *   Default constructor, it sets the path of the file in the system
	 *   @param path Path to the file (absolute or relative)
         */
	ClamFile(std::string path);

	/**
	 *  Sets if the file is/has a virus
	 *  @param stat true if is infected, false otherwise.
         */
	void setInfected( bool stat);


	/**
	 *  This method sets de virus name
	 *  @param virname Registred name of the virus
         */
	void setVirName(std::string virname);


	/**
	 *  Tests if the file is infected
	 *  @return true if is infected, false otherwise.
	 */
	bool isInfected();

	/**
	 *  Gets the registered name of the virus.
	 *  return the name of the virus, a empty string otherwise
	 */
	std::string getVirName();


protected:
/**
 *   virus name
 */
std::string m_virname;

/**
 * true if is infected, false otherwise
 */
bool m_status;
};

#endif
