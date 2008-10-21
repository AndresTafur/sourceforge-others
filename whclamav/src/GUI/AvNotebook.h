/*  This file is part of WhiteHawkClamav,
 *  Copyright (C) 2007 - 2008 Jorge Tafur <darkhawk665@users.sf.net>.
 *
 *   WhiteHawkClamav is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   WhiteHawkClamav is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with WhiteHawkClamav.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <wx/aui/auibook.h>

#include "AvPanel.hh"
#include "StatusPanel.hh"

#ifndef _AVNOTEBOOK_H_
#define _AVNOTEBOOK_H_



class AvNotebook : public wxAuiNotebook
{
public:
    AvNotebook(wxWindow *parent, wxAnimationCtrl *load,int id);

    void loadDb();

    void insertStatus();

    void insertScan();



protected:
AvPanel	      *m_scan;
StatusPanel   *m_status;
wxAnimationCtrl *m_load;
};



#endif // AVNOTEBOOK_H_INCLUDED
