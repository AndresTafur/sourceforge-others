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


#include "StatusPanel.hh"
#include "../ClamLayer/ClamavInstance.hh"


	StatusPanel::StatusPanel(wxWindow *parent) : wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTAB_TRAVERSAL)
	{
      wxBoxSizer *summary = new wxBoxSizer(wxVERTICAL);


	  wxBoxSizer  *sizer = new wxBoxSizer(wxVERTICAL);
	  wxGridSizer *grid  = new wxGridSizer(2,2);
      wxTextCtrl  *age   = new wxTextCtrl(this,wxID_ANY);
      wxTextCtrl  *quar  = new wxTextCtrl(this,wxID_ANY);


      wxString str, str2;


        str   << WhiteHawkClamav::ClamavInstance::getInstance()->getDatabaseAge() << wxT(" days");
        str2  << 0 << wxT(" files");    //TODO quarentine

        age->SetValue(str);
        quar->SetValue(str2);

        age->Disable();
        quar->Disable();

		grid->Add( new wxStaticText(this,wxID_ANY,wxT("Database age:")));
		grid->Add( age);
		grid->Add( new wxStaticText(this,wxID_ANY,wxT("Quarentine:")));
		grid->Add( quar);

        summary->AddSpacer(40);
        summary->Add(grid,1,wxEXPAND);

		sizer->AddSpacer(40);
		sizer->Add(summary,0,wxEXPAND|wxALIGN_CENTER|wxALL,10);
		sizer->AddSpacer(40);


		this->SetSizer(sizer);
	}


