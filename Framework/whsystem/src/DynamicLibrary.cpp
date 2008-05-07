#include "DynamicLibrary.hh"
#include <unistd.h>

//TODO: what happend here?
extern int uselib(const char *path);

WhiteHawkSystem::DynamicLibrary::DynamicLibrary(std::string path, int flag)
{
       handler = dlopen(path.c_str(), flag);
}


void* WhiteHawkSystem::DynamicLibrary::getSymbol(std::string symbol)
{
    return dlsym(handler,symbol.c_str());
}



bool WhiteHawkSystem::DynamicLibrary::close()
{
    return (dlclose(handler)==0);
}

bool WhiteHawkSystem::DynamicLibrary::use(std::string path)
{
    //return (uselib(path.c_str())==0);
}

WhiteHawkSystem::DynamicLibrary::~DynamicLibrary()
{
    this->close();
}
