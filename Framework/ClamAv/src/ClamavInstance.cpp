
#include "ClamavInstance.hh"



	bool WhiteHawkClamav::ClamavInstance::loadDatabase()
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
			    return false;
			}

        dbLoaded = true;
        return true;
	}


	bool WhiteHawkClamav::ClamavInstance::scanFile(ClamFile file)
	{
   	 struct cl_limits limits;
	 const char *name;
	 int status;

		memset(&limits, 0, sizeof(struct cl_limits));
		limits.maxfiles    = 1000;
		limits.maxfilesize = 10 * 1048576;
		limits.maxreclevel = 5;
		limits.maxmailrec = 64;
		limits.maxratio = 200;

		listener->onScan(file);


		status = cl_scanfile( file.getPath().c_str(), &name, NULL, engine,&limits, CL_SCAN_STDOPT);

		if( status == CL_VIRUS)
		{
			file.setVirName(name);
			file.setInfected(true);
			listener->onVirus(file);
		}
	    else if(status != CL_CLEAN)
	        	listener->onError(file, cl_strerror(status));

        return true;
	}


	void WhiteHawkClamav::ClamavInstance::setListener(ClamavEvtListener *listener)
	{
	  this->listener = listener;
	}


	bool WhiteHawkClamav::ClamavInstance::isDBLoaded()
	{
	  return dbLoaded;
	}

	void WhiteHawkClamav::ClamavInstance::destroy()
	{
	  cl_free(engine);
	}

