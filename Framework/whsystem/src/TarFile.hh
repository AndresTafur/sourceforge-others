
#ifndef _TAR_FILE_
#define _TAR_FILE_


#include "WhiteHawkSystem.hh"
#include "TarResource.hh"
#include <string>
#include <libtar.h>

class WhiteHawkSystem::TarFile
{
public:

    TarFile(std::string path);


	/* recomended strip the initial '/'
	 */
	WhiteHawkSystem::TarResource* getResource(std::string name);

	WhiteHawkSystem::TarResource* getNextResource();


    bool append(std::string path,std::string savedName = "");

    bool append(WhiteHawkSystem::FileInfo *file,std::string savedName = "");

    bool appendTree( std::string path,std::string savedName = "");

    bool appendTree(WhiteHawkSystem::SystemPath *path, std::string savedName = "");

	bool extractResource(std::string name, std::string path );

	bool extractResource(WhiteHawkSystem::TarResource *resource, std::string path );

    bool extractAll(std::string path);

    bool close();


protected:
TAR *dir;
std::string path;
};
#endif
