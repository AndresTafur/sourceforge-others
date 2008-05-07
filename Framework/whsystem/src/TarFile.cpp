#include "TarFile.hh"
#include <fcntl.h>



    WhiteHawkSystem::TarFile::TarFile(std::string path)
    {
        tar_open(&dir,(char*)path.c_str(),NULL,O_RDONLY,0,0);
        this->path = path;
    }

    WhiteHawkSystem::TarResource*  WhiteHawkSystem::TarFile::getResource(std::string name)
    {
      WhiteHawkSystem::TarResource *tmp;

        do
        {
           tmp = getNextResource();

            if(!tmp)
              return NULL;

            if( tmp->getName().compare(name) != 0)
              return tmp;

            free(tmp);

        }while(true);
    }

    WhiteHawkSystem::TarResource* WhiteHawkSystem::TarFile::getNextResource()
    {
        if( th_read(dir) == -1)
            return NULL;

        return (new WhiteHawkSystem::TarResource(dir));
    }


    bool WhiteHawkSystem::TarFile::extractResource(TarResource *resource, std::string path )
	{
		return resource->extract(path);
	}


    bool WhiteHawkSystem::TarFile::extractAll(std::string path)
    {
        WhiteHawkSystem::TarResource *res = getNextResource();

            if( path.at( path.length()-1 ) != '/')
                path.append(1,'/');


            while( res != NULL)
            {
                res->extract(path);
                free(res);
                res = getNextResource();
            }

            free(res);
    }

    bool WhiteHawkSystem::TarFile::close()
	{
		return tar_close(dir) == 0;
	}
