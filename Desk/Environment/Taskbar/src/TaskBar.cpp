
#include "Clock.hh"
#include "TrayPanel.hh"
#include "WindowList.hh"

#include "wxCircleToggleButton.hh"

#include "TaskBar.hh"


    TaskBar::TaskBar(wxString str, SystemUtils *sysUtils): DockPanel(wxPoint(0,sysUtils->screenHeight()-29),wxSize(sysUtils->screenWidth(),29))
     {

	wxBoxSizer *sizer;
	wxBitmap bmp( str + wxT("/data/pix/menu.png"),wxBITMAP_TYPE_ANY);
	wxBitmap bmp2( str + wxT("/data/pix/menuh.png"),wxBITMAP_TYPE_ANY);
	wxStaticLine *line, *line2;
	int num;


		path   = str;
		sizer  = new wxBoxSizer(wxHORIZONTAL);
		btn    = new wxCircleToggleButton(this,wxID_OK,bmp,bmp2);

		frame  = new WhiteHawkMenuFrame(str,btn);
		line   = new wxStaticLine(this, wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLI_VERTICAL,wxT(""));
		line2  = new wxStaticLine(this, wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLI_VERTICAL,wxT(""));
		list   = new WindowList(this, wxID_ANY,sysUtils);
		date   = new Clock(this, wxID_ANY);
		tray   = new TrayPanel(this);


        m_menu     = new wxMenu;
        m_sysUtils = new SystemUtils();
		m_coordy   = sysUtils->screenHeight()-33;

      //  tray->getSelection();
        this->createDeskButton();
        this->setDockable();



		btn->SetToolTip("Haga click aqui para iniciar");


		sizer->Add(btn,0,wxFIXED_MINSIZE);
		sizer->Add(list,1,wxEXPAND|wxCENTER|wxTOP,0);

		sizer->Add(line,0,wxSHAPED|wxLEFT|wxRIGHT,1);
		sizer->Add(m_deskbtn,0,wxFIXED_MINSIZE|wxCENTER);

		sizer->Add(line2,0,wxSHAPED|wxLEFT|wxRIGHT,1);
		sizer->Add(tray,0,wxCENTER);
		sizer->Add(date,0,wxFIXED_MINSIZE|wxCENTER);




		this->SetSizer(sizer);
        this->Layout();

	}



    wxButton* TaskBar::createDeskButton()
    {
        wxMenuItem **items;
        int desks;

            desks     = m_sysUtils->getDesktops();

            m_deskbtn = new wxButton(this,DESKBTN,_T(""),wxDefaultPosition,wxDefaultSize,wxNO_BORDER,wxDefaultValidator,_T(""));
            items     = (wxMenuItem**) malloc( sizeof(wxMenuItem)*desks);


            for(int i=0; i < desks; i++)
            {
                items[i] = new wxMenuItem(m_menu,i,(wxString("Desk ")) << (char)(49+i),wxT(""),wxITEM_RADIO);
                m_menu->Append(items[i]);
                Connect(i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(TaskBar::changeDesk));
            }

            m_deskbtn->SetLabel(  (wxString("")) << (char)(49+m_sysUtils->getCurrentDesk()) );
            m_deskbtn->SetBackgroundColour("LIGHT STEEL BLUE");
            m_deskbtn->SetSize(20,25);
            m_deskbtn->SetFont( wxFont(8,wxFONTFAMILY_DEFAULT,0,wxFONTWEIGHT_BOLD,false,"",wxFONTENCODING_DEFAULT));
            m_deskbtn->SetToolTip("Cambia el escritorio actual");

        return  m_deskbtn;
    }


	WindowList* TaskBar::getWndListPanel()
	{
            return list;
    }


	void TaskBar::ShowMenu( wxCommandEvent &evt)
	{
		  frame->runMenu(m_coordy);
	}



	void TaskBar::showDeskSelector(wxCommandEvent &evt)
	{
		m_deskbtn->PopupMenu(m_menu,0,0);
	}


    void TaskBar::onChangeDesk(int desknum)
    {

      wxString str("");

		 str << desknum;

		 m_deskbtn->SetLabel(str);
         m_menu->Check(desknum-1,true);
    }


	void TaskBar::changeDesk(wxCommandEvent &evt)
	{
	  int deskNum = evt.GetId();

		m_sysUtils->setCurrentDesktop(deskNum);
	}


BEGIN_EVENT_TABLE(TaskBar,wxFrame)
EVT_BUTTON(wxID_OK,TaskBar::ShowMenu)
EVT_BUTTON(DESKBTN,TaskBar::showDeskSelector)
END_EVENT_TABLE()

