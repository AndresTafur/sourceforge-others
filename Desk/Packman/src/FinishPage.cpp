#include "FinishPage.hh"


	  FinishPage::FinishPage(wxWindow *parent, wxString name) : Page(parent)
	  {
	    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

	    wxStaticText *title = new wxStaticText(this,wxID_ANY,wxT("Instalacion Satisfactoria:\n\n"),wxDefaultPosition,wxDefaultSize,0,wxT(""));

	    wxStaticText *text = new wxStaticText(this,wxID_ANY,
		name + wxT(" ha sido instalado satisfactoriamente en su sistema, ahora se encuentra en el repositorio de paquetes.")
		wxT("\n\n\nPara mas informacion acerca de la instalacion y administracion de paquetes por favor ingrese a \"Ayuda y Soporte\" del menu."));

		text->Wrap(620);
		sizer->Add(title);
		sizer->AddSpacer(10);
		sizer->Add(text);

		this->SetSizer(sizer);
		this->Fit();
	  }

	  void FinishPage::OnPresent()
	  {

	  }
