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

    WhiteHawkUtil::AbstractFile::AbstractFile() : WhiteHawkUtil::FileInfo("")
	{

	}


	WhiteHawkUtil::AbstractFile::AbstractFile(std::string path) : WhiteHawkUtil::FileInfo(path)
	{

	}


	bool WhiteHawkUtil::AbstractFile::CreateSymLink(std::string path)
	{
	   if(symlink(getFullName().c_str(), path.c_str()) == 0)
            return true;

       fprintf(stderr,"%s",strerror(errno));
      return false;
	}


    bool WhiteHawkUtil::AbstractFile::Rename(std::string name)
	{
	    if( rename(getFullName().c_str(), name.c_str()) == 0)
            return true;

       fprintf(stderr,"%s",strerror(errno));
        return false;
	}


	bool WhiteHawkUtil::AbstractFile::Chown(uid_t user, gid_t group)
	{
	    if( chown(getFullName().c_str(),user, group) == 0)
            return true;

       fprintf(stderr,"%s",strerror(errno));
        return false;
	}


    bool WhiteHawkUtil::AbstractFile::Chmod(mode_t mode)
    {
       if( chmod(getFullName().c_str(),mode) == 0)
            return true;

       fprintf(stderr,"%s",strerror(errno));
        return false;
    }

    bool WhiteHawkUtil::AbstractFile::Move(std::string path)
	{
	    return Rename(path);
	}



    bool WhiteHawkUtil::AbstractFile::Remove()
    {
        if( remove(getFullName().c_str()) == 0)
            return true;

        fprintf(stderr,"%s",strerror(errno));
      return false;
    }


	 bool WhiteHawkUtil::AbstractFile::operator == (short type)
	 {
            if( type == WhiteHawkUtil::AbstractFile::ABS_DIR)
                return isDirectory();
            if( type == WhiteHawkUtil::AbstractFile::ABS_FILE)
                return isFile();

        return isDevice();
     }




     bool WhiteHawkUtil::AbstractFile::operator != (WhiteHawkUtil::AbstractFile obj)
	 {
            return  (getFullName().compare(obj.getFullName()));
     }

