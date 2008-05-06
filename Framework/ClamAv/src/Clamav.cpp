#include "Clamav.hh"
#include <SystemPath.hh>


    WhiteHawkClamav::Clamav::Clamav() : WhiteHawkSystem::Thread()
    {
            id = 0;
    }

    void WhiteHawkClamav::Clamav::scanSubFolder(std::string path)
    {
         WhiteHawkSystem::SystemPath  fs(path);

           do
           {
                ClamFile file( fs.getNextFile().getPath());

                if(!file.isDevice() && !file.getPath().empty())
                {
                    if( file.isDirectory() )
                        scanSubFolder( file.getPath() );
                    else
                    {
                        file.setId(id);
                        this->scanFile(file);
                        id++;
                    }
                }
           }while( !fs.isEnd() );
    }

	void WhiteHawkClamav::Clamav::ThreadRoutine()
	{
		if( defaultPath.empty())
			return;


            ClamFile tmp(defaultPath);

            if(!tmp.isDevice())
            {
                if( tmp.isFile() )
                    this->scanFile(tmp);
       		    else
                    scanSubFolder(defaultPath);
            }
		listener->onFinish();
	}

	void WhiteHawkClamav::Clamav::startScan(std::string path)
	{
	    if( isDBLoaded())
	    {
            defaultPath = path;
            Create();
	    }
	}

	int WhiteHawkClamav::Clamav::getTotalFiles()
	{
	  return m_total;
	}

   	int WhiteHawkClamav::Clamav::getDatabaseAge()
   	{
      	  return 0;
   	}

   	void WhiteHawkClamav::Clamav::onTerminate()
   	{
		listener->onFinish();
   	}

