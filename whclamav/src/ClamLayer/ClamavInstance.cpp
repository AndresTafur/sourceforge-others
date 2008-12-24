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

#include "ClamavInstance.hh"

#include <string.h>
#include <Exception.hh>

WhiteHawkClamav::ClamavInstance *WhiteHawkClamav::ClamavInstance::sm_instance = NULL;
WhiteHawkClamav::ClamavScanner  *WhiteHawkClamav::ClamavInstance::sm_scanner = NULL;



    WhiteHawkClamav::ClamavInstance::ClamavInstance()
    {
           m_engine = NULL;
    }


    WhiteHawkClamav::ClamavInstance* WhiteHawkClamav::ClamavInstance::getInstance()
    {
        if( sm_instance == NULL)
            sm_instance = new ClamavInstance();
        return sm_instance;
    }

    WhiteHawkClamav::ClamavScanner* WhiteHawkClamav::ClamavInstance::getScanner()
    {
        if( sm_scanner == NULL)
            sm_scanner = new ClamavScanner(WhiteHawkClamav::ClamavInstance::getInstance()->getHandler());
        return sm_scanner;
    }


	void WhiteHawkClamav::ClamavInstance::loadDatabase()
	{
	   int ret;
	   unsigned int sigs = 0;

            m_dbdir    = cl_retdbdir();
		    m_engine = NULL;
			memset(&m_dbstat, 0, sizeof(struct cl_stat));


            cl_statinidir(m_dbdir,&m_dbstat);
			cl_load(m_dbdir,&m_engine, &sigs, CL_DB_STDOPT);

			if((ret = cl_build(m_engine)))
			{
			    cl_free(m_engine);
			    m_engine = NULL;
			    throw WhiteHawkSystem::Exception(cl_strerror(ret));
			}
	}


    void WhiteHawkClamav::ClamavInstance::updateEngine()
    {
	   int ret;
	   unsigned int sigs = 0;

            if(cl_statchkdir(&m_dbstat) == 1)
            {
                m_dbdir = cl_retdbdir();
                cl_free(m_engine);
                m_engine = NULL;

                cl_load(m_dbdir,&m_engine, &sigs, CL_DB_STDOPT);

                if((ret = cl_build(m_engine)))
                {
                    cl_free(m_engine);
                    m_engine = NULL;
                    throw WhiteHawkSystem::Exception(cl_strerror(ret));
                }
                cl_statinidir(m_dbdir, &m_dbstat);
            }

    }


   	int WhiteHawkClamav::ClamavInstance::getDatabaseAge()
   	{
      	  return 0;
   	}

    struct cl_engine* WhiteHawkClamav::ClamavInstance::getHandler()
   	{
      	  return m_engine;
   	}


    bool WhiteHawkClamav::ClamavInstance::isDbLoaded()
    {
        return NULL != m_engine;
    }

    void WhiteHawkClamav::ClamavInstance::destroy()
    {
        if( sm_instance )
            delete sm_instance;
    }


    WhiteHawkClamav::ClamavInstance::~ClamavInstance()
    {
        if( NULL != m_engine)
        {
            cl_free(m_engine);
            m_engine = NULL;
        }


        if( sm_scanner != NULL)
            delete sm_scanner;
    }
