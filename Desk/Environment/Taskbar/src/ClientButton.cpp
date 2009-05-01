#include "ClientButton.hh"





    void DragController::Notify()
    {
        if(m_wnd)
            WindowController::getInstance()->setActiveWindow(m_wnd);
    }

    bool DragController::OnDropFiles(wxCoord x, wxCoord y,const wxArrayString &arr)
    {
        return true;
    }

    wxDragResult  DragController::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
    {
            Start(800, true);
    }

    void DragController::OnLeave()
    {
       Stop();
    }



   ClientButton::ClientButton(wxWindow* parent,wxWindowID id, Window window) : wxToggleButton(parent, id,wxT(""), wxDefaultPosition, wxSize(160,27),wxBU_EXACTFIT|wxBU_TOP)
	{
	  XWMHints *hints;
	  this->m_xwindow  = window;
      this->m_marked = false;


        if( m_label.IsEmpty() )
        {
            m_label = wxT("Ventana sin titulo");
            this->SetLabel(m_label);
        }

       m_menu = new wxMenu();
       m_desk = new wxMenu();
       m_ctrl = new DragController();

       m_ctrl->setWindow(m_xwindow);

	   m_menu->Append(MINIMIZE, wxT("Mi&nimizar"),wxT("Reduce la ventana a un boton"), wxITEM_NORMAL);
	   m_menu->Append(MAXIMIZE, wxT("&Restaurar"),wxT("Restaurar"), wxITEM_NORMAL);
	   m_menu->Append(START_MOVING, wxT("&Mover"),wxT("Mueve esta ventana"), wxITEM_NORMAL);
	   m_menu->Break();
	   m_menu->Append(START_RESIZING, wxT("&Redimensionar"),wxT("Redimensionar"), wxITEM_NORMAL);
	   m_menu->Append(0,wxT("&Mover a"),m_desk,wxT("Cambia el escritorio de la ventana"));
	   m_menu->AppendSeparator();
	   m_menu->Append(wxID_CLOSE, wxT("&Cerrar"),wxT("Cierra la ventana"), wxITEM_NORMAL);

       hints =  XGetWMHints(WindowManager::getInstance()->getDisplay(), window);

       if(hints && hints->icon_pixmap != 0)
       {
            GdkPixmap *px  =   gdk_pixmap_foreign_new (hints->icon_pixmap);
            GdkPixmap *px2 =   gdk_pixmap_foreign_new (hints->icon_mask);
            GtkWidget  *img;
                if(px)
                {
                     img = gtk_image_new_from_pixmap(px,px2);
                       gtk_widget_set_size_request(img,16,16);

                     gtk_button_set_image (GTK_BUTTON( this->GetHandle()),img);
                     gtk_button_set_image_position(GTK_BUTTON( this->GetHandle()), GTK_POS_LEFT);

                }

       }

      //  fprintf(stderr,"%s",hints->icon_pixmap);







 	  this->SetToolTip(m_label);
	  this->GetToolTip()->SetDelay(550);
	  this->updateName();
	  this->GetParent()->GetSizer()->Add(this);
	  this->SetDropTarget(m_ctrl);
	}

    void ClientButton::setMark(bool mark)
    {
      m_marked = mark;
    }

    void ClientButton::updateName()
    {
        if(m_xwindow)
        {
            m_label = wxString::FromAscii(WindowController::getInstance()->getWindowName(m_xwindow));
            m_label =m_label.Length() > 15 ? (m_label.substr(0,14)+wxT("...")) :m_label;
            gtk_button_set_label (GTK_BUTTON( this->GetHandle()), m_label.ToAscii()  );
        }
    }

	wxString ClientButton::GetRealName()
	{
	  return m_label;
	}

	Window ClientButton::GetXWindow()
	{
	  return m_xwindow;
	}


    void ClientButton::CloseXWindow()
    {
	    if(m_xwindow)
	      WindowController::getInstance()->closeWindow(m_xwindow);
    }

    void ClientButton::Maximize(wxCommandEvent &evt)
	{
	    if(m_xwindow)
            WindowController::getInstance()->setActiveWindow(m_xwindow);
	}

	void ClientButton::Minimize(wxCommandEvent &evt)
	{
	    if(m_xwindow)
            WindowController::getInstance()->iconifyWindow(m_xwindow);
	}

	void ClientButton::CloseWnd(wxCommandEvent &evt)
	{
          this->CloseXWindow();
	}

	void ClientButton::StartMoving(wxCommandEvent &evt)
	{
	    if(m_xwindow)
            WindowController::getInstance()->startMoveWindow(m_xwindow);
	}

	void ClientButton::StartResizing(wxCommandEvent &evt)
	{
	    if(m_xwindow)
            WindowController::getInstance()->startSizeWindow(m_xwindow);
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
            m_desk->Remove(DESKTOP_1+i);
            str = wxT("Escritorio &");
            str << i;
            m_desk->Append(DESKTOP_1+i, str,str, wxITEM_NORMAL);
            Connect(DESKTOP_1+i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(ClientButton::onDeskChange));
       }

        m_desk->FindItemByPosition(  WindowController::getInstance()->getWndDesktop(m_xwindow)  )->Enable(false);
 	    PopupMenu(m_menu);
	}

    void ClientButton::onDeskChange(wxCommandEvent &evt)
	{
	    if(m_xwindow)
          WindowController::getInstance()->setWndDesktop(m_xwindow,evt.GetId()-DESKTOP_1-1);
    }




BEGIN_EVENT_TABLE(ClientButton,wxToggleButton)
EVT_RIGHT_UP(ClientButton::onRightClick)
EVT_MENU(MINIMIZE,ClientButton::Minimize)
EVT_MENU(MAXIMIZE,ClientButton::Maximize)
EVT_MENU(START_MOVING,ClientButton::StartMoving)
EVT_MENU(START_RESIZING,ClientButton::StartResizing)
EVT_MENU(wxID_CLOSE,ClientButton::CloseWnd)
END_EVENT_TABLE()

