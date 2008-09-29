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

#ifndef _WH_EXCEPTION_
#define _WH_EXCEPTION_

#include <string>
#include <exception>
#include "WhiteHawkSystem.hh"

/**
 *	Exception manager. This class manage any exception.
 */
class WhiteHawkSystem::Exception : public std::exception
{
public:


	/**
	 *   Default Constructor. it initialize the object with a message.
	 *   @param msg Error message.
	 *   @param method Method of the ocurred exception.
	 */
	 Exception(std::string msg = "",std::string method = "");


	/**
	 *   Gets the message. returns the message of this exception.
	 *   @return msg Error message.
	 */
    std::string getMessage();

	/**
	 *   Gets the method. returns the method of this exception.
	 *   @return msg Error message.
	 */
    std::string getMethod();


	/**
	 *   Prints the exception mesage.
	 */
	 void print();

	/**
	 *
	 *   Inherited by exception returns the cause.
	 *   @return Cause of the exception.
	 */
	  const char*  what() const throw ();


    ~Exception() throw ();

protected:
/**
 * Message. Exception message.
 */
std::string  m_msg;
std::string  m_met;
std::string  m_lin;

};
#endif
