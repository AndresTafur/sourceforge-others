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

        /**
         *  Default constructor.
         *  @param path Path to the dynamic library.
         *  @param flag dl system flag ( RTLD_NOW or RTLD_GLOBAL.
         */
        DynamicLibrary(std::string path, int flag = RTLD_NOW|RTLD_GLOBAL);

        /**
         *  Returns a function pointer of the loaded library.
         *  @param symbol Function name.
         *  @return Function pointer.
         */
        void* getSymbol(std::string symbol);

        /**
         *  Closes de library.
         *  @return true if it was sucessfully removed.
         */
        bool close();

        /**
         *  Selects a path to be used for a library
         *  @param path path to be used
         *  @return true if it could be changed, false otherwise
         */
        bool use(std::string path);

        /**
         * Default destructor.
         */
        ~DynamicLibrary();

protected:
void *m_handler;

};
#endif
