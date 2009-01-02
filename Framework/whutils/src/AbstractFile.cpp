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

#include "FileInfo.hh"
#include "AbstractFile.hh"

    WhiteHawkSystem::AbstractFile::AbstractFile() : WhiteHawkSystem::FileInfo("")
	{

	}


	WhiteHawkSystem::AbstractFile::AbstractFile(std::string path) : WhiteHawkSystem::FileInfo(path)
	{

	}


	bool WhiteHawkSystem::AbstractFile::CreateSymLink(std::string path)
	{
	   if(symlink(this->m_path.c_str(), path.c_str()) == 0)
            return true;
      return false;
	}


    bool WhiteHawkSystem::AbstractFile::Rename(std::string name)
	{
	    if( rename(this->m_path.c_str(), name.c_str()) == 0)
            return true;
        return false;
	}


	bool WhiteHawkSystem::AbstractFile::Chown(uid_t user, gid_t group)
	{
	    if( chown(m_path.c_str(),user, group) == 0)
            return true;
        return false;
	}


    bool WhiteHawkSystem::AbstractFile::Chmod(mode_t mode)
    {
       if( chmod(m_path.c_str(),mode) == 0)
            return true;
        return false;
    }

    bool WhiteHawkSystem::AbstractFile::Move(std::string path)
	{
	    return Rename(path);
	}



    bool WhiteHawkSystem::AbstractFile::Remove()
    {
        if( remove(m_path.c_str()) == 0)
            return true;
      return false;
    }


	 bool WhiteHawkSystem::AbstractFile::operator == (short type)
	 {
            if( type == WhiteHawkSystem::AbstractFile::ABS_DIR)
                return isDirectory();
            if( type == WhiteHawkSystem::AbstractFile::ABS_FILE)
                return isFile();

        return isDevice();
     }




     bool WhiteHawkSystem::AbstractFile::operator != (WhiteHawkSystem::AbstractFile obj)
	 {
            return  (m_path.compare(obj.getPath()));
     }

