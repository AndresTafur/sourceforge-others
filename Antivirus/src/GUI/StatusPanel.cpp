#include "StatusPanel.hh"

	StatusPanel::StatusPanel(wxWindow *parent, WhiteHawkClamav::Clamav *mgr) : wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTAB_TRAVERSAL)
	{
      wxBoxSizer *summary = new wxBoxSizer(wxVERTICAL);


	  wxBoxSizer  *sizer = new wxBoxSizer(wxVERTICAL);
	  wxGridSizer *grid  = new wxGridSizer(2,2);
      wxTextCtrl  *age   = new wxTextCtrl(this,wxID_ANY);
      wxTextCtrl  *quar  = new wxTextCtrl(this,wxID_ANY);


      wxString str, str2;


        str   << mgr->getDatabaseAge() << wxT(" days");
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


