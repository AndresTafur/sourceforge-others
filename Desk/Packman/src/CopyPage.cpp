#include "CopyPage.hh"


	  CopyPage::CopyPage(wxWindow *parent, Package *package) : Page(parent)
	  {
	    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	    wxBoxSizer *prog  = new wxBoxSizer(wxHORIZONTAL);

	    wxStaticText *title = new wxStaticText(this,wxID_ANY,wxT("Se estan copiando los ficheros del paquete, por favor aguarde:\t\t\t\t\t\t"),wxDefaultPosition,wxDefaultSize,0,wxT(""));

        wxGauge *gauge = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_SMOOTH);


        gauge->SetValue(50);

		sizer->Add(title);
        sizer->AddSpacer(70);
		sizer->Add(prog,0,wxALIGN_CENTER|wxEXPAND);

        prog->AddSpacer(50);
		prog->Add(gauge,1,wxALIGN_CENTER);
		this->SetSizer(sizer);
		this->Fit();
		parent->Layout();
	  }

	  void CopyPage::OnPresent()
	  {

	  }
