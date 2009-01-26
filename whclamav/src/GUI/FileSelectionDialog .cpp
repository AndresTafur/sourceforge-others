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

#include "FileSelectionDialog.hh"


    FileSelectionDialog::FileSelectionDialog(wxWindow *parent) :wxDialog(parent, wxID_ANY, wxT("File to scan"),wxDefaultPosition,wxSize(500,400))
    {
        wxBoxSizer   *sizer = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer   *ctrl  = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText *text  = new wxStaticText(this,wxID_ANY,wxT("Please select the file or folder to be scanned: \n"));


        browser = new wxGenericDirCtrl(this,wxID_ANY,wxDirDialogDefaultFolderStr,wxDefaultPosition,wxDefaultSize,wxDIRCTRL_SHOW_FILTERS|wxDIRCTRL_SELECT_FIRST|wxDIRCTRL_3D_INTERNAL|wxSUNKEN_BORDER);



        sizer->Add(text,0,wxEXPAND|wxALL,5);
        sizer->Add(browser,1,wxEXPAND|wxALL,5);
        sizer->Add( this->CreateButtonSizer(wxOK|wxCANCEL),0,wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL,2);
        this->SetSizer(sizer);

    }



    wxString FileSelectionDialog::getFullPath()
    {
        return browser->GetPath() ;
    }
