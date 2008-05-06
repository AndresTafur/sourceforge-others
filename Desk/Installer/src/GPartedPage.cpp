
class GPartedPage : public Page
{
public:

	GPartedPage(wxWindow *parent) : Page(parent)
	{
	   wxBoxSizer *sizer  = new wxBoxSizer(wxVERTICAL);
	   wxButton   *parted = new wxButton(this,100,_("Iniciar &GParted"),wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,_(""));
	  


	  wxStaticText *title = new wxStaticText(this,wxID_ANY,wxT("Particionado de disco:"),wxDefaultPosition,wxDefaultSize,0,wxT(""));

	  wxStaticText *text = new wxStaticText(this,wxID_ANY,"Para instalar whiteHawk se requiere que exista espacio "
		"libre en el disco duro para hacer almenos una particion Swap y una particion ReiserFS o Ext3, "
		"si ya tiene instalado un sistema operativo puede redimensionar su particion y usar el espacio libre.\n\n"
		"Nota: se suguiere hacer una copia de seguridad de sus datos.\n\n"
		"Para realizar las particiones por favor presione el boton \"Iniciar GParted\"."
		,wxDefaultPosition,wxDefaultSize,0,wxT(""));
	
		text->Wrap(620);

		sizer->Add(title);
		sizer->AddSpacer(10);
		sizer->Add(text);
		sizer->AddSpacer(30);
		sizer->Add(parted,0,wxEXPAND,2);

		this->SetSizer(sizer);
		this->Fit();
	}


	void runParted(wxCommandEvent &e)
	{
		system("gparted");
	}


	void OnPresent()
	{

	}

private:
DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(GPartedPage,wxPanel)
EVT_BUTTON(100,GPartedPage::runParted)
END_EVENT_TABLE()
