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

#include "Exception.hh"


	WhiteHawkUtil::Exception::Exception(std::string msg,std::string method)
	{
	  m_msg = msg;
	  m_met = method;
	}

	void WhiteHawkUtil::Exception::print()
	{
	  std::string buff;

        buff = "From: " + m_met + "\n\t" + m_msg;

	  perror( buff.c_str());
	}


    std::string WhiteHawkUtil::Exception::getMessage()
    {
        return m_msg;
    }


    std::string WhiteHawkUtil::Exception::getMethod()
    {
        return m_met;
    }


    const char*  WhiteHawkUtil::Exception::what()
    const throw ()
    {
        return m_msg.c_str();
    }



   WhiteHawkUtil::Exception::~Exception()
   throw ()
   {

   }
