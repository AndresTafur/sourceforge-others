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
