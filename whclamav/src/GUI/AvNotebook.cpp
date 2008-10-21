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

#include "AvNotebook.h"


    AvNotebook::AvNotebook(wxWindow *parent, wxAnimationCtrl *load,int id) : wxAuiNotebook(parent, id,wxDefaultPosition,wxDefaultSize,wxAUI_NB_TOP|wxAUI_NB_TAB_MOVE|wxAUI_NB_WINDOWLIST_BUTTON)
    {
            this->m_load = load;

            m_status  = new StatusPanel(this);
            m_scan    = new AvPanel(this,load);

            this->AddPage(m_status, wxT("Status"));
            this->AddPage(m_scan, wxT("Scan Files"), true);
    }



    void AvNotebook::insertStatus()
    {
       int stat = GetPageIndex(m_status);
            SetSelection(stat);
    }


    void AvNotebook::insertScan()
    {
       int stat =  GetPageIndex(m_scan);

         SetSelection(stat);
    }
