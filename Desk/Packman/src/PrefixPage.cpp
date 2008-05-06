#include "PrefixPage.hh"


	  PrefixPage::PrefixPage(wxWindow *parent, Package *package) : Page(parent)
	  {
	    wxBoxSizer  *sizer = new wxBoxSizer(wxVERTICAL);
	    wxGridSizer *ctrl  = new wxGridSizer(2,4);

	    wxStaticText *title = new wxStaticText(this,wxID_ANY,wxT(" Por favor indique las rutas por defecto donde desea instalar el paquete:"),wxDefaultPosition,wxDefaultSize,0,wxT(""));


		sizer->Add(title);
        sizer->AddSpacer(70);
		sizer->Add(ctrl,1,wxALIGN_CENTER|wxEXPAND);

		ctrl->Add( new wxStaticText(this,wxID_ANY,wxT("bin:")),0,wxALIGN_CENTER);
		ctrl->Add( new wxTextCtrl(this,wxID_ANY,wxT("")),1,wxEXPAND|wxALIGN_CENTER);
		ctrl->Add( new wxStaticText(this,wxID_ANY,wxT("lib:")),0,wxALIGN_CENTER);
		ctrl->Add( new wxTextCtrl(this,wxID_ANY,wxT("")),1,wxEXPAND|wxALIGN_CENTER);
		ctrl->Add( new wxStaticText(this,wxID_ANY,wxT("include:")),0,wxALIGN_CENTER);
		ctrl->Add( new wxTextCtrl(this,wxID_ANY,wxT("")),1,wxEXPAND|wxALIGN_CENTER);
		ctrl->Add( new wxStaticText(this,wxID_ANY,wxT("man:")),0,wxALIGN_CENTER);
		ctrl->Add( new wxTextCtrl(this,wxID_ANY,wxT("")),1,wxEXPAND|wxALIGN_CENTER);


		this->SetSizer(sizer);
		this->Fit();
		parent->Layout();
	  }

	  void PrefixPage::OnPresent()
	  {

	  }
