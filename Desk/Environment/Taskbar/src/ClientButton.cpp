#include "ClientButton.hh"
#include <wx/tooltip.h>
#include <wx/wx.h>

   ClientButton::ClientButton(wxWindow* parent,wxWindowID id, Window window,wxString label) : wxToggleButton(parent, id, label.SubString(0,16), wxDefaultPosition, wxDefaultSize,wxBU_EXACTFIT|wxBU_TOP)
	{
	  this->xwindow  = window;
	  this->label    = label;
      this->m_marked = false;

       m_menu = new wxMenu();
       m_desk = new wxMenu();

	   m_menu->Append(1, wxT("Mi&nimizar"),wxT("Reduce la ventana a un boton"), wxITEM_NORMAL);
	   m_menu->Append(2, wxT("&Restaurar"),wxT("Restaurar"), wxITEM_NORMAL);
	   m_menu->Append(3, wxT("&Mover"),wxT("Mueve esta ventana"), wxITEM_NORMAL);
	   m_menu->Break();
	   m_menu->Append(4, wxT("&Redimensionar"),wxT("Redimensionar"), wxITEM_NORMAL);
	   m_menu->Append(0,wxT("&Mover a"),m_desk,wxT("Cambia el escritorio de la ventana"));
	   m_menu->AppendSeparator();
	   m_menu->Append(wxID_CLOSE, wxT("&Cerrar"),wxT("Cierra la ventana"), wxITEM_NORMAL);


 	  this->SetToolTip(label);
	  this->GetToolTip()->SetDelay(550);
	  AddToTaskbar();
	}


	void ClientButton::AddToTaskbar()
	{
 	  GetParent()->GetSizer()->Add(this);
	}

    void ClientButton::setMark(bool mark)
    {
            m_marked = mark;
    }

    void ClientButton::updateName()
    {
        this->SetLabel( WindowController::getInstance()->getWindowName(xwindow) );
    }


    void ClientButton::CloseXWindow()
    {
	    if(xwindow)
	     WindowController::getInstance()->closeWindow(xwindow);
    }


	wxString ClientButton::GetRealName()
	{
	  return label;
	}

	Window ClientButton::GetXWindow()
	{
	  return xwindow;
	}

    bool ClientButton::isMarked()
    {
           return m_marked;
    }


	void ClientButton::onRightClick(wxMouseEvent &evt)
	{
	  short desks = DeskController::getInstance()->getDesktops();
      wxString  str;


       for(int i=1; i <= desks; i++)
       {
            m_desk->Remove(i+5);
            str = wxT("Escritorio &");
            str << i;
            m_desk->Append(i+5, str,str, wxITEM_NORMAL);
             Connect(i+5,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(ClientButton::onDeskChange));

       }
	   PopupMenu(m_menu);
	}

    void ClientButton::onDeskChange(wxCommandEvent &evt)
	{
	    //if(xwindow)
         //   WindowController::getInstance()->setActiveWindow(xwindow);
	}


	void ClientButton::Maximize(wxCommandEvent &evt)
	{
	    if(xwindow)
            WindowController::getInstance()->setActiveWindow(xwindow);
	}


	void ClientButton::Minimize(wxCommandEvent &evt)
	{
	    if(xwindow)
            WindowController::getInstance()->iconifyWindow(xwindow);
	}

	void ClientButton::StartMoving(wxCommandEvent &evt)
	{
	    if(xwindow)
            WindowController::getInstance()->startMoveWindow(xwindow);
	}

	void ClientButton::StartResizing(wxCommandEvent &evt)
	{
	    if(xwindow)
            WindowController::getInstance()->startSizeWindow(xwindow);
	}

	void ClientButton::CloseWnd(wxCommandEvent &evt)
	{
          this->CloseXWindow();
	}

BEGIN_EVENT_TABLE(ClientButton,wxToggleButton)
EVT_RIGHT_UP(ClientButton::onRightClick)
EVT_MENU(1,ClientButton::Minimize)
EVT_MENU(2,ClientButton::Maximize)
EVT_MENU(3,ClientButton::StartMoving)
EVT_MENU(4,ClientButton::StartResizing)
EVT_MENU(wxID_CLOSE,ClientButton::CloseWnd)
END_EVENT_TABLE()

