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

#include "DynamicLibrary.hh"
#include "Exception.hh"
#include <unistd.h>

//TODO: what happend here?
extern int uselib(const char *path);

WhiteHawkSystem::DynamicLibrary::DynamicLibrary(std::string path, int flag)
{
       handler = dlopen(path.c_str(), flag);
}


void* WhiteHawkSystem::DynamicLibrary::getSymbol(std::string symbol)
{
    if( !handler)
         throw (Exception("Failed. Bad lubrary handler"));

    return dlsym(handler,symbol.c_str());
}



bool WhiteHawkSystem::DynamicLibrary::close()
{
    if( !handler)
     throw (Exception("Failed. Bad lubrary handler"));

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
