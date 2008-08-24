#include "Clamav.hh"
#include <SystemPath.hh>
#include <string.h>

WhiteHawkClamav::Clamav *WhiteHawkClamav::Clamav::m_instance = NULL;


    WhiteHawkClamav::Clamav::Clamav() : WhiteHawkSystem::Thread()
    {
            m_curr   = 0;
            m_total  = 0;
    }


   WhiteHawkClamav::Clamav* WhiteHawkClamav::Clamav::getInstance()
    {
        if( m_instance == NULL)
            m_instance = new Clamav();
        return m_instance;
    }


    void WhiteHawkClamav::Clamav::setPath(std::string path)
    {
        m_path  = path;
    }


        void WhiteHawkClamav::Clamav::scanSubFolder(ClamFile objDir)
        {
            struct dirent *red;
            DIR *buff;

            if( !objDir.isDirectory())
            {
                objDir.setId(m_curr);
                this->scanFile(objDir,m_total);
                m_curr++;
                return;
            }

            if( objDir.getPath().at( objDir.getPath().length()-1) != '/')
                objDir.setPath(objDir.getPath() + "/");

            buff = opendir(objDir.getPath().c_str());

            if( !buff)
                return;

            while( NULL != (red = readdir(buff)) )
	        {
               ClamFile tmp( objDir.getPath() + red->d_name);

                    if(tmp.isDirectory())
                    {
                        if( strcmp(red->d_name,".") != 0 && strcmp(red->d_name,"..") != 0  )
                                scanSubFolder(tmp);
                    }
                    else if( tmp.isFile())
                    {
                        tmp.setId(m_curr);
                        this->scanFile(tmp,m_total);
                        m_curr++;
                    }

             }
             closedir(buff);
        }


	void WhiteHawkClamav::Clamav::ThreadRoutine()
	{
		if( m_path.empty())
			return;

            loadDatabase();
            m_total = getTotalFiles();

            ClamFile tmp(m_path);

            if(!tmp.isDevice())
            {
                if( tmp.isFile() )
                    this->scanFile(tmp,m_total);
       		    else
                    scanSubFolder( ClamFile(m_path));
            }
			for( std::list<ClamavEvtListener*>::iterator beg = listeners.begin(); beg != listeners.end(); beg++)
                (*beg)->onFinish();
	}

	void WhiteHawkClamav::Clamav::startScan()
	{
	        m_total = 0;
	        m_curr  = 0;
	        fprintf(stderr,"Starting  scan.\n");
            Create();
	}

	long long WhiteHawkClamav::Clamav::getTotalFiles()
	{
	  WhiteHawkSystem::SystemPathCount count;
      WhiteHawkSystem::AbstractFile file(m_path);

            count    = WhiteHawkSystem::SystemPath::getCount(file);

        return count.getFilesCount() + count.getLinksCount() + count.getBlockDevicesCount() + count.getCharDevicesCount();
	}

   	int WhiteHawkClamav::Clamav::getDatabaseAge()
   	{
      	  return 0;
   	}

   	void WhiteHawkClamav::Clamav::onTerminate()
   	{
		for( std::list<ClamavEvtListener*>::iterator beg = listeners.begin(); beg != listeners.end(); beg++)
                (*beg)->onFinish();
   	}

