#include "TarResource.hh"
#include "SystemPath.hh"


	WhiteHawkSystem::TarResource::TarResource(TAR *handler)
	{
		eof = false;
		this->handler = handler;
		this->name    = th_get_pathname(handler);
	}


	void WhiteHawkSystem::TarResource::setName(std::string name)
	{
		this->name = name;
	}


	std::string WhiteHawkSystem::TarResource::getName()
	{
		return name;
	}


	std::string WhiteHawkSystem::TarResource::getContent()
	{
	   char buf[T_BLOCKSIZE];
	   int   i,k;
	   std::string str;

	        for (i = th_get_size(handler); i > 0; i -= T_BLOCKSIZE)
            {
                k = tar_block_read(handler, buf);
                if (k != T_BLOCKSIZE)
                  break;
            }

            str = buf;

	    return str;
	}


	bool WhiteHawkSystem::TarResource::extract()
	{
	    return  tar_extract_file(handler,(char*)name.c_str()) == 0;
	}


    bool WhiteHawkSystem::TarResource::extract(std::string path)
	{
        FILE *fdout;
        int i, k;
        char buf[T_BLOCKSIZE];

            if( path.at(path.length()) != '/')
                path += '/';


            WhiteHawkSystem::SystemPath::mkdirhier(path.c_str());

            path += th_get_pathname(handler);


            fdout = fopen(path.c_str(),"ab");

			fprintf(fdout, getContent().c_str());

            fclose(fdout);

        return true;
	}


	bool WhiteHawkSystem::TarResource::isOpen()
	{
		if(handler)
		  return true;
	   return false;
	}

	bool WhiteHawkSystem::TarResource::isEof()
	{
	  return eof;
	}


	void WhiteHawkSystem::TarResource::rewind()
	{
	 // zzip_rewind(handler);
	}


	void WhiteHawkSystem::TarResource::close()
	{
	   //zzip_file_close(handler);
	}


