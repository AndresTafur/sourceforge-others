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


    WhiteHawkClamav::ClamavScanner::ClamavScanner(struct cl_engine *engine): WhiteHawkUtil::Thread()
    {
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
            std::string currPath;
            DIR *buff;

                try
                {

                    if( !objDir.isDirectory())
                        this->scanFile(objDir);
                    else
                    {

                        if( objDir.getFullName().at( objDir.getFullName().length()-1) != '/')
                            objDir.setFullName(objDir.getFullName() + '/');

                        buff = opendir(objDir.getFullName().c_str());

                        if( buff)
                        {
                            while( NULL != (red = readdir(buff)) )
                            {
                              ClamFile tmp( objDir.getFullName() + red->d_name);

                                /*
                                 * Temporal fix, if a file fails continue with the next
                                 * in the folder instead of leave the entire folder.
                                 */

                                try
                                {
                                    if(tmp.isDirectory())
                                    {
                                        if( strcmp(red->d_name,".") != 0 && strcmp(red->d_name,"..") != 0  )
                                            if( closedir(buff) == 0)
                                            {
                                                currPath = red->d_name;
                                                scanSubFolder(tmp);
                                                buff = opendir(objDir.getFullName().c_str());

                                                do
                                                {
                                                    red = readdir(buff);

                                                    if( red == NULL)
                                                        break;

                                                }while( currPath.compare(red->d_name) != 0 );
                                            }
                                    }
                                    else if( tmp.isFile())
                                    {
                                        for( std::list<ClamavEvtListener*>::iterator beg = m_listeners.begin(); beg != m_listeners.end(); beg++)
                                            (*beg)->onScan(tmp);

                                        if( this->scanFile(tmp) )
                                            for( std::list<ClamavEvtListener*>::iterator beg = m_listeners.begin(); beg != m_listeners.end(); beg++)
                                                (*beg)->onVirus(tmp);
                                    }
                                }
                                catch(WhiteHawkUtil::Exception e)
                                {
                                    e.print();
                                }
                            }
                            closedir(buff);
                        }
                    }
                }
                catch(WhiteHawkUtil::Exception e)
                {
                    e.print();
                }
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

        file.setInfected(false);


		status = cl_scanfile( file.getFullName().c_str(), &name, NULL, m_engine,&limits, CL_SCAN_STDOPT);

		if( status == CL_VIRUS)
		{
			file.setVirName(name);
			file.setInfected(true);
			return true;
		}
	    else if(status != CL_CLEAN)
	        for( std::list<ClamavEvtListener*>::iterator beg = m_listeners.begin(); beg != m_listeners.end(); beg++)
            (*beg)->onError(file, cl_strerror(status));

        return false;
	}


	void WhiteHawkClamav::ClamavScanner::run()
	{
	  WhiteHawkUtil::SystemPathCount count;
      WhiteHawkUtil::AbstractFile file(m_path);


            if( m_path.empty())
                return;


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

	void WhiteHawkClamav::ClamavScanner::startScan()
	{
            startThread(0);
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

