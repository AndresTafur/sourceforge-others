
#include <stdlib.h>

#include "ZipResource.hh"
#include "SystemPath.hh"

	WhiteHawkSystem::ZipResource::ZipResource(std::string path)
	{
		handler = zzip_fopen(path.c_str(), "rb");
		eof = false;
	}

	WhiteHawkSystem::ZipResource::ZipResource(ZZIP_FILE *file)
	{
		handler = file;
		eof = false;
	}


	void WhiteHawkSystem::ZipResource::setName(std::string name)
	{
		this->name = name;
	}


	std::string WhiteHawkSystem::ZipResource::getName()
	{
		return name;
	}


	std::string WhiteHawkSystem::ZipResource::getContent(int size)
	{
	   char *buff = (char*) malloc( (size+1) * sizeof( char ) );
	   int   bytes;
	   std::string str;

			bytes = zzip_file_read(handler, buff, size);
			if(bytes < size )
				eof = true;

			buff[bytes] = '\0';

			str.append(buff);
			free(buff);
	    return str;
	}


    bool WhiteHawkSystem::ZipResource::extract()
	{
	  FILE *file;;

	  std::string str;


		file = fopen( name.c_str(),"wb");

		if(file)
		    while( !isEof()  )
                fprintf(file,"%s",getContent().c_str());
		else
		  return false;

      fclose(file);
      free(file);
	  return true;
	}



	bool WhiteHawkSystem::ZipResource::extract(std::string path)
	{
	  FILE *file;;

	  std::string str;


        WhiteHawkSystem::SystemPath::mkdirhier(path.c_str());


		file = fopen( (path+name).c_str(),"wb");

		if( file)
		    while( !isEof()  )
			fprintf(file,"%s",getContent().c_str());
		else
		  return false;
	  return true;
	}


	bool WhiteHawkSystem::ZipResource::isOpen()
	{
		if( handler)
		  return true;
	   return false;
	}

	bool WhiteHawkSystem::ZipResource::isEof()
	{
	  return eof;
	}

	zzip_off_t WhiteHawkSystem::ZipResource::getOffset()
	{
	  return zzip_tell(handler);
	}

	void WhiteHawkSystem::ZipResource::setOffset(zzip_off_t offset, int pos)
	{
		zzip_seek(handler, offset, SEEK_SET);
	}


	void WhiteHawkSystem::ZipResource::rewind()
	{
	  zzip_rewind(handler);
	}


	void WhiteHawkSystem::ZipResource::close()
	{
	   zzip_file_close(handler);
	}

