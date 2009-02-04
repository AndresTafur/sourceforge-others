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
#include "Exception.hh"

	WhiteHawkUtil::FileInfo::FileInfo()
	{
		setFullName(".");
	}

	WhiteHawkUtil::FileInfo::FileInfo(std::string path)
	{
	  setFullName(path);
	}



	void WhiteHawkUtil::FileInfo::setFullName(std::string path)
	{
	  int index;

        m_fullName = path;
 	    index      = path.find_last_of ('/');

        if( index == path.size()-1)
            index = path.find_last_of ('/',index-1);

 	    m_path = path.substr(0,index+1);
 	    m_name = path.substr(index+1);
	}


    bool WhiteHawkUtil::FileInfo::setPermission(mode_t mode)
    {
          return  chmod(m_path.c_str(),mode) == 0;
    }


	bool WhiteHawkUtil::FileInfo::setLastAccess(WhiteHawkUtil::Time &time)
	{
        struct utimbuf times;


        times.actime  =  time.getHandler();
        times.modtime =  modTime.getHandler();

        if( utime(m_path.c_str(),&times) == 0)
        {
            accTime = time;
            return true;
        }
        return false;
	}


	bool WhiteHawkUtil::FileInfo::setLastModification(WhiteHawkUtil::Time &time)
	{
      struct utimbuf times;


        times.actime  =  accTime.getHandler();
        times.modtime =  time.getHandler();

        if( utime(m_path.c_str(),&times) == 0)
        {
            modTime = time;
            return true;
        }
        return false;
	}


    bool WhiteHawkUtil::FileInfo::setOwner(uid_t id)
    {
          return  lchown(m_path.c_str(), id, -1) == 0;
    }


    bool WhiteHawkUtil::FileInfo::setGroup(gid_t id)
    {
          return lchown(m_path.c_str(),-1, id) == 0;
    }


	std::string WhiteHawkUtil::FileInfo::getPath()
	{
	  return m_path;
	}

	std::string WhiteHawkUtil::FileInfo::getName()
	{

	  return m_name;
	}

    std::string WhiteHawkUtil::FileInfo::getFullName()
    {
        return m_fullName;
    }


	int WhiteHawkUtil::FileInfo::getSize()
	{
	    if( lstat(getFullName().c_str(), &fileStatus) != 0)
            throw Exception("Warning: "+getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::getSize");

	  return fileStatus.st_size;
	}


	WhiteHawkUtil::Time WhiteHawkUtil::FileInfo::getLastAccess()
	{
	    if( lstat(getFullName().c_str(), &fileStatus) != 0 )
            throw Exception("Warning: "+getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::getLastAccess");

        accTime.setTime( fileStatus.st_atime  );
        return accTime;
	}

	WhiteHawkUtil::Time WhiteHawkUtil::FileInfo::getLastModification()
	{
	  if( lstat(getFullName().c_str(), &fileStatus) != 0 )
           throw Exception("Warning: "+getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::getLastModification");

	    modTime.setTime( fileStatus.st_atime  );
        return modTime;
	}


    bool WhiteHawkUtil::FileInfo::exist()
    {
        return access(getFullName().c_str(), F_OK) == 0;
    }


	bool WhiteHawkUtil::FileInfo::isFile()
	{
	    if( lstat(getFullName().c_str(), &fileStatus) != 0)
	        throw Exception("Warning: "+getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::isFile");

		return S_ISREG(fileStatus.st_mode);
	}

	bool WhiteHawkUtil::FileInfo::isUserReadable()
	{
	    if( lstat(getFullName().c_str(), &fileStatus) != 0)
            throw Exception("Warning: "+getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::isUserReadable");
        return access(m_path.c_str(),R_OK) == 0;
    }

	bool WhiteHawkUtil::FileInfo::isUserWritable()
	{
	    if( lstat(getFullName().c_str(), &fileStatus) != 0)
            throw Exception("Warning: "+getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::isUserWritable");
        return access(m_path.c_str(),W_OK) == 0;
    }

    bool WhiteHawkUtil::FileInfo::isUserExecutable()
    {
        if( lstat(getFullName().c_str(), &fileStatus) != 0)
            throw Exception("Warning: "+getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::isUserExecutable");
        return access(m_path.c_str(),X_OK) == 0;
    }

    bool WhiteHawkUtil::FileInfo::isUserRWX()
    {
        return isUserReadable() && isUserWritable() && isUserExecutable();
    }

	bool WhiteHawkUtil::FileInfo::isLink()
	{
	    if( lstat(getFullName().c_str(), &fileStatus) != 0)
            throw Exception("Warning: "+getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::isLink");
		return S_ISLNK(fileStatus.st_mode);
	}

	bool WhiteHawkUtil::FileInfo::isDirectory()
	{
	    if( lstat(getFullName().c_str(), &fileStatus) != 0)
            throw Exception("Warning: "+getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::isDirectory");
		return S_ISDIR(fileStatus.st_mode);
	}

	bool WhiteHawkUtil::FileInfo::isCharDevice()
	{
	    if( lstat(getFullName().c_str(), &fileStatus) != 0)
            throw Exception("Warning: "+getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::isCharDevice");
		return S_ISCHR(fileStatus.st_mode);
	}

	bool WhiteHawkUtil::FileInfo::isBlockDevice()
	{
	    if(lstat(getFullName().c_str(), &fileStatus) != 0)
            throw Exception(getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::isBlockDevice");
		return S_ISBLK(fileStatus.st_mode);
	}

	bool WhiteHawkUtil::FileInfo::isFIFO()
	{
	    if( lstat(getFullName().c_str(), &fileStatus) != 0)
            throw Exception(getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::isFIFO");
		return S_ISFIFO(fileStatus.st_mode);
	}

	bool WhiteHawkUtil::FileInfo::isSocket()
	{
	    if( lstat(getFullName().c_str(), &fileStatus) != 0)
            throw Exception(getFullName() +" lstat failed","WhiteHawkUtil::FileInfo::isSocket");
		return S_ISSOCK(fileStatus.st_mode);
	}

	bool WhiteHawkUtil::FileInfo::isDevice()
	{
	   return (isCharDevice() || isBlockDevice());
	}

	bool WhiteHawkUtil::FileInfo::operator == (std::string path)
	{
            return this->getFullName() == path;
    }

	bool WhiteHawkUtil::FileInfo::operator != (std::string path)
	{
            return !(this->getFullName() == path);
    }
