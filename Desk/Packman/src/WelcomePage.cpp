#include "WelcomePage.hh"


	  WelcomePage::WelcomePage(wxWindow *parent, wxString name) : Page(parent)
	  {
	    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

	    wxStaticText *title = new wxStaticText(this,wxID_ANY,wxT("Bienvenido:"),wxDefaultPosition,wxDefaultSize,0,wxT(""));

	    wxStaticText *text = new wxStaticText(this,wxID_ANY,wxT("Este asistente le guiara en el proceso de ")
		wxT("instalacion de ") + name + wxT(" en su sistema, si es un usuario inexperto puede obtener informacion ")
		wxT("de los pasos de instalacion en \"Ayuda y Soporte\" del menu.")
		wxT("\n\nPor favor presione el boton \"Siguiente\".")
		,wxDefaultPosition,wxDefaultSize,0,wxT(""));

		text->Wrap(620);
		sizer->Add(title);
		sizer->AddSpacer(10);
		sizer->Add(text);

		this->SetSizer(sizer);
		this->Fit();
	  }

	  void WelcomePage::OnPresent()
	  {

	  }
