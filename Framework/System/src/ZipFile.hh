
#ifndef _ZIP_FILE_
#define _ZIP_FILE_

#include "ZipResource.hh"

//TODO: Compression

class WhiteHawkSystem::ZipFile
{
public:


	ZipFile(std::string path);


	/* recomended strip the initial '/'
	 */
	WhiteHawkSystem::ZipResource*  getResource(std::string name);

	WhiteHawkSystem::ZipResource* getNextResource();


	bool extractResource(std::string name, std::string path );


	bool extractResource(WhiteHawkSystem::ZipResource *resource, std::string path );


    bool extractAll(std::string path);


	bool isOpen();


	bool close();

    ~ZipFile();

protected:
ZZIP_DIR* dir;

};
#endif
