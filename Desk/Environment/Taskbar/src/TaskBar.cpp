
#include "Clock.hh"
#include "TrayPanel.hh"
#include "WindowList.hh"

#include "wxCircleToggleButton.hh"
#include "DeskCtrl.hh"
#include "TaskBar.hh"
#include "WindowManager.hh"



    TaskBar::TaskBar(wxString str): DockPanel(wxPoint(0,WindowManager::getInstance()->screenHeight()-29),wxSize(WindowManager::getInstance()->screenWidth(),29),wxT("WhiteHawk taskbar"))
     {

	   wxBoxSizer *sizer;
	   wxBitmap bmp( str + wxT("/data/pix/menu.png"),wxBITMAP_TYPE_ANY);
	   wxBitmap bmp2( str + wxT("/data/pix/menuh.png"),wxBITMAP_TYPE_ANY);
	   wxStaticLine *line, *line2;
	   DeskCtrl *deskBtn;
	   int num;


		path    = str;
		sizer   = new wxBoxSizer(wxHORIZONTAL);
		btn     = new wxCircleToggleButton(this,wxID_OK,bmp,bmp2);
		frame   = new WhiteHawkMenuFrame(str,btn);
		line    = new wxStaticLine(this, wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLI_VERTICAL,wxT(""));
		line2   = new wxStaticLine(this, wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLI_VERTICAL,wxT(""));
		list    = new WindowList(this, wxID_ANY);
		date    = new Clock(this, wxID_ANY);
		tray    = new TrayPanel(this);
        deskBtn = new DeskCtrl(this);


        m_menu     = new wxMenu;
		m_coordy   = WindowManager::getInstance()->screenHeight()-33;


      //  tray->getSelection();
        this->setDockable();



		btn->SetToolTip("Haga click aqui para iniciar");


		sizer->Add(btn,0,wxFIXED_MINSIZE);
		sizer->Add(list,1,wxEXPAND|wxCENTER|wxTOP,0);

		sizer->Add(line,0,wxSHAPED|wxLEFT|wxRIGHT,1);
		sizer->Add(deskBtn,0,wxFIXED_MINSIZE|wxCENTER);

		sizer->Add(line2,0,wxSHAPED|wxLEFT|wxRIGHT,1);
		sizer->Add(tray,0,wxCENTER);
		sizer->Add(date,0,wxFIXED_MINSIZE|wxCENTER);




		this->SetSizer(sizer);
        this->Layout();

	}


	WindowList* TaskBar::getWndListPanel()
	{
            return list;
    }


	void TaskBar::ShowMenu( wxCommandEvent &evt)
	{
		  frame->runMenu(m_coordy);
	}




BEGIN_EVENT_TABLE(TaskBar,wxFrame)
EVT_BUTTON(wxID_OK,TaskBar::ShowMenu)
END_EVENT_TABLE()

