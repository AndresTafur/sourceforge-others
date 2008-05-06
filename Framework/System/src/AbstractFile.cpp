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
