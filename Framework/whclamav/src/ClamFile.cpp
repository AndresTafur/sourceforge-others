#include "ClamFile.hh"

	WhiteHawkClamav::ClamFile::ClamFile(std::string path) : WhiteHawkSystem::AbstractFile(path)
	{
		status = false;
	}


	void WhiteHawkClamav::ClamFile::setInfected( bool stat)
	{
		status = stat;
	}

	void WhiteHawkClamav::ClamFile::setVirName(std::string virname)
	{
	  this->virname = virname;
	}


	void WhiteHawkClamav::ClamFile::setId( int id)
	{
		this->id = id;
	}

	bool WhiteHawkClamav::ClamFile::isInfected()
	{
	   return status;
	}


	std::string WhiteHawkClamav::ClamFile::getVirName()
	{
	  return virname;
	}

	int WhiteHawkClamav::ClamFile::getId()
	{
		return id;
	}

