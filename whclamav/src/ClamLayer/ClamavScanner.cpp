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

#include "ClamavScanner.hh"
#include <SystemPath.hh>
#include <string.h>
#include <Exception.hh>


    WhiteHawkClamav::ClamavScanner::ClamavScanner(struct cl_engine *engine): WhiteHawkSystem::Thread()
    {
            m_curr   = 0;
            m_total  = 0;
            m_engine = engine;
    }


    void WhiteHawkClamav::ClamavScanner::setEngine(struct cl_engine *engine)
    {
        m_engine = engine;
    }


    void WhiteHawkClamav::ClamavScanner::setPath(std::string path)
    {
        m_path  = path;
    }

    std::string WhiteHawkClamav::ClamavScanner::getPath()
    {
        return m_path;
    }

        void WhiteHawkClamav::ClamavScanner::scanSubFolder(ClamFile objDir)
        {
            struct dirent *red;
            DIR *buff;

            if( !objDir.isDirectory())
            {
                objDir.setId(m_curr);
                this->scanFile(objDir);
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
                        this->scanFile(tmp);
                        m_curr++;
                    }

             }
             closedir(buff);
        }


    bool WhiteHawkClamav::ClamavScanner::scanFile(ClamFile &file)
	{
   	 struct cl_limits limits;
	 const char *name;
	 int status;

        this->sleep(10);
		memset(&limits, 0, sizeof(struct cl_limits));
		limits.maxfiles    = 1000;
		limits.maxfilesize = 10 * 1048576;
		limits.maxreclevel = 16;
		limits.maxscansize = 100 * 1048576;

        for( std::list<ClamavEvtListener*>::iterator beg = m_listeners.begin(); beg != m_listeners.end(); beg++)
            (*beg)->onScan(file,m_total);


		status = cl_scanfile( file.getPath().c_str(), &name, NULL, m_engine,&limits, CL_SCAN_STDOPT);

		if( status == CL_VIRUS)
		{
			file.setVirName(name);
			file.setInfected(true);
			for( std::list<ClamavEvtListener*>::iterator beg = m_listeners.begin(); beg != m_listeners.end(); beg++)
                (*beg)->onVirus(file);
		}
	    else if(status != CL_CLEAN)
	        for( std::list<ClamavEvtListener*>::iterator beg = m_listeners.begin(); beg != m_listeners.end(); beg++)
            (*beg)->onError(file, cl_strerror(status));

        return true;
	}


	void WhiteHawkClamav::ClamavScanner::run()
	{
	  WhiteHawkSystem::SystemPathCount count;
      WhiteHawkSystem::AbstractFile file(m_path);

      try
      {
		if( m_path.empty())
			return;

            count   = WhiteHawkSystem::SystemPath::getCount(file);
            m_total = count.getFilesCount();

            ClamFile tmp(m_path);

            if(!tmp.isDevice())
            {
                if( tmp.isFile() )
                    this->scanFile(tmp);
       		    else if( tmp.isDirectory());
                    scanSubFolder( ClamFile(m_path));
            }

			for( std::list<ClamavEvtListener*>::iterator beg = m_listeners.begin(); beg != m_listeners.end(); beg++)
                (*beg)->onFinish();
      }
      catch(WhiteHawkSystem::Exception ex)
      {
         ex.print();
         for( std::list<ClamavEvtListener*>::iterator beg = m_listeners.begin(); beg != m_listeners.end(); beg++)
                (*beg)->onFinish();
      }
	}

	void WhiteHawkClamav::ClamavScanner::startScan()
	{
	        m_total = 0;
	        m_curr  = 0;
            startThread(0);
	}


	long long WhiteHawkClamav::ClamavScanner::getTotalFiles()
	{
            return m_total;
	}


    void WhiteHawkClamav::ClamavScanner::addListener(ClamavEvtListener *listener)
	{
        m_listeners.push_back(listener);
	}

    void WhiteHawkClamav::ClamavScanner::removeListener(ClamavEvtListener *listener)
	{
        m_listeners.remove(listener);
	}


   	void WhiteHawkClamav::ClamavScanner::onTerminate()
   	{
		for( std::list<ClamavEvtListener*>::iterator beg = m_listeners.begin(); beg != m_listeners.end(); beg++)
                (*beg)->onFinish();
   	}

