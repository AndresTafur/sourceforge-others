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

#include "StatusPanel.hh"
#include "../ClamLayer/ClamavInstance.hh"


#undef wxT
#define wxT(data) wxString::FromAscii(data)


	StatusPanel::StatusPanel(wxWindow *parent) : wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTAB_TRAVERSAL)
	{
      wxBoxSizer  *summary   = new wxStaticBoxSizer(wxVERTICAL,this,wxT(_("Summary")));
      wxBoxSizer  *versions  = new wxStaticBoxSizer(wxVERTICAL,this,wxT(_("Versions")));
	  wxBoxSizer  *sizer     = new wxBoxSizer(wxVERTICAL);
	  wxGridSizer *grid      = new wxGridSizer(2,3);
	  wxGridSizer *grid2     = new wxGridSizer(2,3);
      wxTextCtrl  *age       = new wxTextCtrl(this,wxID_ANY);
	  wxTextCtrl  *quar      = new wxTextCtrl(this,wxID_ANY);
	  wxTextCtrl  *lastscan  = new wxTextCtrl(this,wxID_ANY);
	  wxTextCtrl  *version   = new wxTextCtrl(this,wxID_ANY);
	  wxTextCtrl  *function  = new wxTextCtrl(this,wxID_ANY);
	  wxTextCtrl  *database  = new wxTextCtrl(this,wxID_ANY);

	  wxString str = wxT("");


        str << WhiteHawkClamav::ClamavInstance::getInstance()->getDatabaseAge();
        age->SetValue(str);

        str = wxT("0 files");    //TODO quarentine
        quar->SetValue(str);

        str = wxT("");
        str << cl_retflevel();
        function->SetValue(str);

        str = wxT("");
        str << wxT(cl_retver());
        version->SetValue(str);

        str = wxT("");
        str << wxT(cl_retdbdir());
	    database->SetValue(str);

        age->SetEditable(false);
        quar->SetEditable(false);
        lastscan->SetEditable(false);
        version->SetEditable(false);
	    function->SetEditable(false);
	    database->SetEditable(false);

		grid->Add( new wxStaticText(this,wxID_ANY,wxT(_("Database age:"))));
		grid->Add( age,1);
		grid->Add( new wxStaticText(this,wxID_ANY,wxT(_("Quarentine:"))));
		grid->Add( quar,1);
		grid->Add( new wxStaticText(this,wxID_ANY,wxT(_("Last scan:"))));
		grid->Add( lastscan,1);

		grid2->Add( new wxStaticText(this,wxID_ANY,wxT(_("Clamav version:"))));
		grid2->Add( version,1);
        grid2->Add( new wxStaticText(this,wxID_ANY,wxT(_("Clamav functionality level:"))));
		grid2->Add( function,1);
		grid2->Add( new wxStaticText(this,wxID_ANY,wxT(_("Clamav database:"))));
		grid2->Add( database,1);


        summary->AddSpacer(20);
        summary->Add(grid,1,wxEXPAND|wxALIGN_CENTER_HORIZONTAL);

        versions->AddSpacer(20);
        versions->Add(grid2,1,wxEXPAND|wxALIGN_CENTER_HORIZONTAL);

		sizer->AddSpacer(40);
		sizer->Add(summary,0,wxEXPAND|wxALIGN_CENTER|wxALL,10);
		sizer->Add(versions,0,wxEXPAND|wxALIGN_CENTER|wxALL,10);
		sizer->AddSpacer(40);

		this->SetSizer(sizer);
	}


