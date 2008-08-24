#include "ClamavInstance.hh"
#include <string.h>
#include <Exception.hh>

	void WhiteHawkClamav::ClamavInstance::loadDatabase()
	{
   	   struct cl_stat dbstat;
	   int ret;
	   unsigned int sigs = 0;

		    engine = NULL;
			memset(&dbstat, 0, sizeof(struct cl_stat));


			cl_load(cl_retdbdir(),&engine, &sigs, CL_DB_STDOPT);

			if((ret = cl_build(engine)))
			{
			    printf("cl_build() error: %s\n", cl_strerror(ret));
			    cl_free(engine);
			    throw( new WhiteHawkSystem::Exception(cl_strerror(ret)));
			}
	}


	bool WhiteHawkClamav::ClamavInstance::scanFile(ClamFile &file, int total)
	{
   	 struct cl_limits limits;
	 const char *name;
	 int status;

		memset(&limits, 0, sizeof(struct cl_limits));
		limits.maxfiles    = 1000;
		limits.maxfilesize = 10 * 1048576;
		limits.maxreclevel = 16;
		limits.maxscansize = 100 * 1048576;

        for( std::list<ClamavEvtListener*>::iterator beg = listeners.begin(); beg != listeners.end(); beg++)
            (*beg)->onScan(file, total);


		status = cl_scanfile( file.getPath().c_str(), &name, NULL, engine,&limits, CL_SCAN_STDOPT);

		if( status == CL_VIRUS)
		{
			file.setVirName(name);
			file.setInfected(true);
			for( std::list<ClamavEvtListener*>::iterator beg = listeners.begin(); beg != listeners.end(); beg++)
                (*beg)->onVirus(file);
		}
	    else if(status != CL_CLEAN)
	        for( std::list<ClamavEvtListener*>::iterator beg = listeners.begin(); beg != listeners.end(); beg++)
            (*beg)->onError(file, cl_strerror(status));

        return true;
	}


	void WhiteHawkClamav::ClamavInstance::addListener(ClamavEvtListener *listener)
	{
        listeners.push_back(listener);
	}


	void WhiteHawkClamav::ClamavInstance::destroy()
	{
	  cl_free(engine);
	}

    WhiteHawkClamav::ClamavInstance::~ClamavInstance()
    {
        this->destroy();
    }
