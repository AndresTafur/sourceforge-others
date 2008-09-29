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
#ifndef _CLAMAV_ENGINE_
#define _CLAMAV_ENGINE_


class ClamavEngine
{
public:

        ClamavEngine();

        void loadDatabase(int option);

        bool hasChanged();



public:

static CL_DEFAULT;
static CL_PHISHING;
static CL_PHISHURL;
static CL_PUNWANTED;
protected:

};
