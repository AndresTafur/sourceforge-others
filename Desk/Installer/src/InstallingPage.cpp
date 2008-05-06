#include "InstallationManager.cpp"

class InstallingPage : public Page
{
public:

	InstallingPage(wxWindow *parent) : Page(parent)
	{

	   sizer  = new wxBoxSizer(wxVERTICAL);
	   wxStaticText  *title;
	   wxStaticText  *text;
	   mgr = new InstallationManager();



	        title = new wxStaticText(this,0,_("Instalando el sistema Base:"),wxDefaultPosition,wxDefaultSize,0,_(""));

	  	text = new wxStaticText(this,wxID_ANY,"Ahora  se procedera  a instalar "
		"lo necesario para el arranque de whiteHawk, despues de este paso "
		"se reiniciara el equipo y se completara la instalacion.\n\n\n"
		,wxDefaultPosition,wxDefaultSize,0,wxT(""));


		status = new wxStaticText(this,wxID_ANY,wxT(""),wxDefaultPosition,wxDefaultSize,0,wxT(""));


		mgr->Create();


		this->SetTargetWindow(this);
		text->Wrap(620);

		sizer->Add(title,0,wxBOTTOM,10);
		sizer->Add(text,0,wxBOTTOM,20);
		sizer->Add(status);


		this->SetSizer(sizer);
		this->Fit();
	}


	void Exit()
	{
	   mgr->Delete();
	}

	void setPath(wxString path)
	{
		mgr->setPath(path);
	}

	void OnPresent()
	{
	  wxString str;
	  

		str =  ((PartitionsPage*)last)->GetRoot();
		mgr->setPath(str);



		status->SetLabel( wxT("Montando particion ") + str + wxT(" como raiz."));
		
		mgr->Run();

	}


protected:
InstallationManager *mgr;
wxBoxSizer    	    *sizer;
wxStaticText 	    *status;
};
