#include "FileInfo.hh"


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


	bool WhiteHawkSystem::FileInfo::setLastAccess(WhiteHawkSystem::Time time)
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


	bool WhiteHawkSystem::FileInfo::setLastModification(WhiteHawkSystem::Time time)
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
	    lstat(m_path.c_str(), &fileStatus);

	  return fileStatus.st_size;
	}


	WhiteHawkSystem::Time WhiteHawkSystem::FileInfo::getLastAccess()
	{
	    if( lstat(m_path.c_str(), &fileStatus) == 0 )
	    	accTime.setTime( fileStatus.st_atime  );

        return accTime;
	}

	WhiteHawkSystem::Time WhiteHawkSystem::FileInfo::getLastModification()
	{
	  if( lstat(m_path.c_str(), &fileStatus) == 0 )
	    modTime.setTime( fileStatus.st_atime  );

        return modTime;
	}


    bool WhiteHawkSystem::FileInfo::exist()
    {
        return access(m_path.c_str(), F_OK) == 0;
    }


	bool WhiteHawkSystem::FileInfo::isFile()
	{
	    lstat(m_path.c_str(), &fileStatus);
		return S_ISREG(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isUserReadable()
	{
	    lstat(m_path.c_str(), &fileStatus);
        return access(m_path.c_str(),R_OK) == 0;
    }

	bool WhiteHawkSystem::FileInfo::isUserWritable()
	{
	    lstat(m_path.c_str(), &fileStatus);
        return access(m_path.c_str(),W_OK) == 0;
    }

    bool WhiteHawkSystem::FileInfo::isUserExecutable()
    {
        lstat(m_path.c_str(), &fileStatus);
        return access(m_path.c_str(),X_OK) == 0;
    }

    bool WhiteHawkSystem::FileInfo::isUserRWX()
    {
        return isUserReadable() && isUserWritable() && isUserExecutable();
    }

	bool WhiteHawkSystem::FileInfo::isLink()
	{
	    lstat(m_path.c_str(), &fileStatus);
		return S_ISLNK(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isDirectory()
	{
	    lstat(m_path.c_str(), &fileStatus);
		return S_ISDIR(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isCharDevice()
	{
		return S_ISCHR(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isBlockDevice()
	{
	    lstat(m_path.c_str(), &fileStatus);
		return S_ISBLK(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isFIFO()
	{
	    lstat(m_path.c_str(), &fileStatus);
		return S_ISFIFO(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isSocket()
	{
	    lstat(m_path.c_str(), &fileStatus);
		return S_ISSOCK(fileStatus.st_mode);
	}

	bool WhiteHawkSystem::FileInfo::isDevice()
	{
	   lstat(m_path.c_str(), &fileStatus);
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
