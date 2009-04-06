#include "WhiteHawkMenuFrame.hh"
#include "RunFrame.hh"


WhiteHawkMenu::WhiteHawkMenu(WhiteHawkMenu *parent,int id,const wxString text, const wxString help,const wxBitmap bitmap) : wxMenuItem(parent->GetMenu(),id,text,help,wxITEM_NORMAL,NULL)
{
	this->SetBitmap(bitmap);
	menu = new wxMenu;
}



WhiteHawkMenu::WhiteHawkMenu(WhiteHawkMenu *parent,int id, const wxString text, const wxString help,const wxString bitmap) : wxMenuItem(parent->GetMenu(),id,text,help,wxITEM_NORMAL,NULL)
{
	wxBitmap bmp(bitmap,wxBITMAP_TYPE_ANY);
	this->SetBitmap(bmp);
	menu = new wxMenu;
}


WhiteHawkMenu::WhiteHawkMenu(wxMenu *parent,int id,const wxString text, const wxString help,const wxBitmap bitmap) : wxMenuItem(parent,id,text,help,wxITEM_NORMAL,NULL)
{
	this->SetBitmap(bitmap);
	menu = new wxMenu;
}



WhiteHawkMenu::WhiteHawkMenu(wxMenu *parent,int id, const wxString text, const wxString help,const wxString bitmap) : wxMenuItem(parent,id,text,help,wxITEM_NORMAL,NULL)
{
	wxBitmap bmp(bitmap,wxBITMAP_TYPE_ANY);
	this->SetBitmap(bmp);
	menu = new wxMenu;
}

	wxMenuItem* WhiteHawkMenu::Append(wxMenuItem* item)
	{
		this->SetSubMenu(menu);
		return (menu->Append(item));
	}

	wxMenuItem* WhiteHawkMenu::Append(int id, const wxString &item, const wxString& helpString)
	{
		this->SetSubMenu(menu);
		return menu->Append(id,item,helpString,wxITEM_NORMAL);
	}


	void WhiteHawkMenu::AppendSeparator()
	{
	  this->SetSubMenu(menu);
	  menu->AppendSeparator();
	}

	void WhiteHawkMenu::Break()
	{
	  menu->Break();
	}

	wxMenu* WhiteHawkMenu::GetMenu()
	{
		return menu;
	}



 WhiteHawkMenuFrame::WhiteHawkMenuFrame(wxString &str, wxCircleToggleButton *btn): wxFrame(NULL,wxID_ANY,wxT(""), wxPoint(0,300), wxDefaultSize, wxFRAME_NO_TASKBAR|wxSTAY_ON_TOP, wxT(""))
        {
	   WhiteHawkMenu *program;

	   WhiteHawkMenu *acceso;
	   WhiteHawkMenu *calc;

	   WhiteHawkMenu *office;
	   WhiteHawkMenu *games;

	   WhiteHawkMenu *inet;
	   WhiteHawkMenu *amul;
	   WhiteHawkMenu *dfast;
	   WhiteHawkMenu *mess;
	   WhiteHawkMenu *nav;


	   WhiteHawkMenu *rep;
	   WhiteHawkMenu *code;
	   WhiteHawkMenu *baker;
	   WhiteHawkMenu *gimp;

	   WhiteHawkMenu *config;
	   WhiteHawkMenu *docum;
	   WhiteHawkMenu *run;
	   WhiteHawkMenu *find;

	   WhiteHawkMenu *help;
	   WhiteHawkMenu *tutorial;

	   WhiteHawkMenu *logout;
	   WhiteHawkMenu *apagar;



		wxBitmap fld(str + wxT("/data/pix/menuFolder.png"),wxBITMAP_TYPE_ANY);



		menu = new wxMenu;
		menu->AppendSeparator();


		program = new WhiteHawkMenu(menu,idle,_T("&Programas"),_T("Abre programas"),str+wxT("/data/pix/prog.png"));

		acceso  = new WhiteHawkMenu(program,idle,wxT("Accesorios"),wxT("Utilidades"),fld);
		calc 	= new WhiteHawkMenu(acceso,ID_CALC,wxT("Calculadora"),wxT("Operaciones"),str+wxT("/data/pix/calc.png"));
		acceso->Append(calc);


		office  = new WhiteHawkMenu(program,idle,wxT("Oficina"),wxT("Office"),fld);


		games  = new WhiteHawkMenu(program,idle,wxT("Juegos"),wxT("Entretenimiento"),fld);



		inet   = new WhiteHawkMenu(program,idle,wxT("Internet"),wxT("Programas de internet"),str+wxT("/data/pix/inet.png"));
		amul   = new WhiteHawkMenu(inet,idle,wxT("Amule"),wxT("Descargas"),str+wxT("/data/pix/amule.png"));
		dfast  = new WhiteHawkMenu(inet,idle,wxT("Descarga de archivos"),wxT("Descargas"),str+wxT("/data/pix/wxdfast.png"));
		mess   = new WhiteHawkMenu(inet,idle,_T("Mensajeria instantanea"),_T("Mensajeria"),str+_T("/data/pix/mess.png"));
		nav    = new WhiteHawkMenu(inet,idle,wxT("Navegador web"),wxT("Navegador"),str+wxT("/data/pix/moz.png"));


		inet->Append(dfast);
		inet->Append(mess);
		inet->Append(nav);





		rep   = new WhiteHawkMenu(program,idle,wxT("Reproductor de medios"),wxT("Reproductor de musica"),str+wxT("/data/pix/mrep.png"));

		code  = new WhiteHawkMenu(program,idle,wxT("CodeBlocks"),wxT("IDE"),str+wxT("/data/pix/code.png"));

		baker = new WhiteHawkMenu(program,idle,wxT("Grabador de CD"),_T("Descargas"),str+wxT("/data/pix/burn.png"));

		gimp  = new WhiteHawkMenu(program,idle,wxT("Gimp"),wxT("Imagenes"),str+wxT("/data/pix/gimp.png"));


		program->Append(acceso);
		program->Append(office);
		program->Append(games);
		program->Append(inet);

		program->Append(code);
		program->Append(gimp);
		program->Append(baker);
		program->Append(rep);




		docum  = new WhiteHawkMenu(menu,idle,_T("Documentos"),_T("Documentos abiertos"),str+ wxT("/data/pix/doc.png"));


		config = new WhiteHawkMenu(menu,idle,wxT("&Configuracion"),_T(""),str+ wxT("/data/pix/config.png"));
		config->Append(ID_CONFIG, wxT("Panel de control"),  wxT("Administracion en general"));
		config->Append(0, wxT("Conexiones de red"),  wxT("Administra las conexiones"));
		config->Append(0, wxT("Impresoras y faxes"), wxT("Administra las impresoras"));
		config->Append(0, wxT("Barra de tareas y Menu"), wxT("Configura la barra de tareas"));


		find = new WhiteHawkMenu(menu,idle,_T("&Buscar"),_T("Busca archivos en el equipo"),str+wxT("/data/pix/find.png"));
		run  = new WhiteHawkMenu(menu,ID_RUN,_T("&Ejecutar"),_T("Ejecuta una aplicacion"),str+wxT("/data/pix/run.png"));
		tutorial  = new WhiteHawkMenu(menu,idle,wxT("&Tutoriales"),wxT("ayuda"),str+wxT("/data/pix/tuto.png"));
		help  = new WhiteHawkMenu(menu,idle,wxT("Ayuda y &soporte"),wxT("ayuda"),str+wxT("/data/pix/help.png"));
		logout = new WhiteHawkMenu(menu,idle,_("&Salir"), _("Sale de la sesion actual"),str+wxT("/data/pix/logout.png"));
		apagar = new WhiteHawkMenu(menu,idle,_T("&Apagar"), _("apaga el PC"), str + wxT("/data/pix/exit.png"));


		menu->Append(program);
		menu->Append(docum);
		menu->Append(config);
		menu->AppendSeparator();
		menu->Append(find);
		menu->Append(tutorial);
		menu->Append(help);
		menu->Append(run);
		menu->AppendSeparator();
		menu->Append(logout);
		menu->Append(apagar);


		path = str;
		this->btn = btn;

		this->SetTitle(wxT("Menu"));
                this->Layout();
		this->Fit();
        }


	void  WhiteHawkMenuFrame::OnShowMenu(wxMenuEvent &evt)
	{
		btn->SetValue(true);
	}

	void  WhiteHawkMenuFrame::OnCloseMenu(wxMenuEvent &evt)
	{
		btn->SetValue(false);
	}


	void  WhiteHawkMenuFrame::runMenu(int y)
	{
		PopupMenu(menu,1,y-(menu->GetMenuItemCount()*25)-3);
	}

	void  WhiteHawkMenuFrame::RunProgram(const char *prog)
	{
		popen(prog,"r");
	}

	void  WhiteHawkMenuFrame::RunDlg( wxCommandEvent &evt)
	{
	        RunFrame *frame = new RunFrame(path);
                frame->Show();
	}


	void  WhiteHawkMenuFrame::RunCfg( wxCommandEvent &evt)
	{
		RunProgram("whitehawk-config");
	}

	void  WhiteHawkMenuFrame::RunTerm( wxCommandEvent &evt)
	{
	        RunProgram("gnome-terminal");
 	}


BEGIN_EVENT_TABLE(WhiteHawkMenuFrame,wxFrame)
EVT_MENU(ID_RUN,WhiteHawkMenuFrame::RunDlg)
EVT_MENU(ID_CONFIG,WhiteHawkMenuFrame::RunCfg)
EVT_MENU(ID_RUN,WhiteHawkMenuFrame::RunDlg)
EVT_MENU(ID_RUN,WhiteHawkMenuFrame::RunDlg)
EVT_MENU(ID_RUN,WhiteHawkMenuFrame::RunDlg)
EVT_MENU_OPEN(WhiteHawkMenuFrame::OnShowMenu)
EVT_MENU_CLOSE(WhiteHawkMenuFrame::OnCloseMenu)
END_EVENT_TABLE()
