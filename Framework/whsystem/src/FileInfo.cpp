#include "FileInfo.hh"
#include "Exception.hh"

	WhiteHawkSystem::FileInfo::FileInfo()
	{
		setPath(".");
	}

	WhiteHawkSystem::FileInfo::FileInfo(std::string path)
	{
	  setPath(path);
	}



	void WhiteHawkSystem::FileInfo::setPath(std::string path)
	{
 	    this->m_path = path;
	}


    bool WhiteHawkSystem::FileInfo::setPermission(mode_t mode)
    {
          return  chmod(m_path.c_str(),mode) == 0;
    }


	bool WhiteHawkSystem::FileInfo::setLastAccess(WhiteHawkSystem::Time &time)
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


	bool WhiteHawkSystem::FileInfo::setLastModification(WhiteHawkSystem::Time &time)
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


    bool WhiteHawkSystem::FileInfo::setOwner(uid_t id)
    {
          return  lchown(m_path.c_str(), id, -1) == 0;
    }


    bool WhiteHawkSystem::FileInfo::setGroup(gid_t id)
    {
          return lchown(m_path.c_str(),-1, id) == 0;
    }


	std::string WhiteHawkSystem::FileInfo::getPath()
	{
	  return m_path;
	}

	std::string WhiteHawkSystem::FileInfo::getName()
	{
	  return m_path; //TODO: finish this thing
	}


	int WhiteHawkSystem::FileInfo::getSize()
	{
	    if( lstat(m_path.c_str(), &fileStatus) != 0)
            throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::getSize");

	  return fileStatus.st_size;
	}


	WhiteHawkSystem::Time WhiteHawkSystem::FileInfo::getLastAccess()
	{
	    if( lstat(m_path.c_str(), &fileStatus) != 0 )
            throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::getLastAccess");

        accTime.setTime( fileStatus.st_atime  );
        return accTime;
	}

	WhiteHawkSystem::Time WhiteHawkSystem::FileInfo::getLastModification()
	{
	  if( lstat(m_path.c_str(), &fileStatus) != 0 )
           throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::getLastModification");

	    modTime.setTime( fileStatus.st_atime  );
        return modTime;
	}


    bool WhiteHawkSystem::FileInfo::exist()
    {
        return access(m_path.c_str(), F_OK) == 0;
    }


	bool WhiteHawkSystem::FileInfo::isFile()
	{
	    if( lstat(m_path.c_str(), &fileStatus) != 0)
	        throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::isFile");

		return S_ISREG(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isUserReadable()
	{
	    if( lstat(m_path.c_str(), &fileStatus) != 0)
            throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::isUserReadable");
        return access(m_path.c_str(),R_OK) == 0;
    }

	bool WhiteHawkSystem::FileInfo::isUserWritable()
	{
	    if( lstat(m_path.c_str(), &fileStatus) != 0)
            throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::isUserWritable");
        return access(m_path.c_str(),W_OK) == 0;
    }

    bool WhiteHawkSystem::FileInfo::isUserExecutable()
    {
        if( lstat(m_path.c_str(), &fileStatus) != 0)
            throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::isUserExecutable");
        return access(m_path.c_str(),X_OK) == 0;
    }

    bool WhiteHawkSystem::FileInfo::isUserRWX()
    {
        return isUserReadable() && isUserWritable() && isUserExecutable();
    }

	bool WhiteHawkSystem::FileInfo::isLink()
	{
	    if( lstat(m_path.c_str(), &fileStatus) != 0)
            throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::isLink");
		return S_ISLNK(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isDirectory()
	{
	    if( lstat(m_path.c_str(), &fileStatus) != 0)
            throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::isDirectory");
		return S_ISDIR(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isCharDevice()
	{
	    if( lstat(m_path.c_str(), &fileStatus) != 0)
            throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::isCharDevice");
		return S_ISCHR(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isBlockDevice()
	{
	    if(lstat(m_path.c_str(), &fileStatus) != 0)
            throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::isBlockDevice");
		return S_ISBLK(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isFIFO()
	{
	    if( lstat(m_path.c_str(), &fileStatus) != 0)
            throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::isFIFO");
		return S_ISFIFO(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isSocket()
	{
	    if( lstat(m_path.c_str(), &fileStatus) != 0)
            throw Exception("File lstat failed","WhiteHawkSystem::FileInfo::isSocket");
		return S_ISSOCK(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isDevice()
	{
	   return (isCharDevice() || isBlockDevice());
	}

	bool WhiteHawkSystem::FileInfo::operator == (std::string path)
	{
            return this->m_path == path;
    }

	bool WhiteHawkSystem::FileInfo::operator != (std::string path)
	{
            return !(this->m_path == path);
    }
