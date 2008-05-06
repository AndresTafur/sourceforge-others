
#ifndef _DYNAMIC_LIBRARY_
#define _DYNAMIC_LIBRARY_

#include <string>
#include <dlfcn.h>
#include "WhiteHawkSystem.hh"

class WhiteHawkSystem::DynamicLibrary
{
public:

        DynamicLibrary(std::string path, int flag = RTLD_NOW|RTLD_GLOBAL);


        void* getSymbol(std::string symbol);

        bool close();

        bool use(std::string path);

        ~DynamicLibrary();

protected:
void *handler;

};
#endif
