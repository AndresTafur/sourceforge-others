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

#include "ClamFile.hh"

	WhiteHawkClamav::ClamFile::ClamFile(std::string path) : WhiteHawkSystem::AbstractFile(path)
	{
		m_status = false;
	}


	void WhiteHawkClamav::ClamFile::setInfected( bool stat)
	{
		m_status = stat;
	}

	void WhiteHawkClamav::ClamFile::setVirName(std::string virname)
	{
	  this->m_virname = virname;
	}


	void WhiteHawkClamav::ClamFile::setId( int id)
	{
		this->m_id = id;
	}

	bool WhiteHawkClamav::ClamFile::isInfected()
	{
	   return m_status;
	}


	std::string WhiteHawkClamav::ClamFile::getVirName()
	{
	  return m_virname;
	}

	int WhiteHawkClamav::ClamFile::getId()
	{
		return m_id;
	}

