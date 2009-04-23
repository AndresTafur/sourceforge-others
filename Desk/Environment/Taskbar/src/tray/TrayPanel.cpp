#include "TrayPanel.hh"


#include "../WindowEventManager.hh"

	TrayPanel::TrayPanel(wxWindow *parent) : wxPanel(parent,wxID_ANY,wxDefaultPosition,wxSize(128,32))
	{

    }

    void TrayPanel::onEvent(Window wnd, Atom atom)
    {

    }

    void TrayPanel::layout(Window wnd)
    {
       std::list<Window>::iterator iter = m_icons.begin();

       ///TODO: SIZE AUTOADJUST
       /*
        int x,y;
            unsigned int size = m_icons.size();

            this->GetPosition(&x, &y);

            x-= 32*(size-1);

            this->SetPosition( wxPoint(x, y));
            this->SetSize(32*size,32);
            this->GetParent()->Layout();
            this->GetParent()->Update();
            XMoveResizeWindow(m_display,m_wnd, x,y, 32*size, 32);
        */

            for(short i=0; iter != m_icons.end(); iter++, i++)
            {
                if( (*iter) != wnd)
                    XMoveResizeWindow(m_display, (*iter), 32*i,0, 24, 24);
            }
    }



  void TrayPanel::getSelection()
  {
     int scr;
     int  orient = 1;
     int width,height,x,y;
     XEvent xev;
     Window oldOwner;
     Atom   orientation;
     Atom xa_xembed;

        this->GetSize(&width, &height);
        this->GetPosition(&x, &y);

        m_display = WindowManager::getInstance()->getDisplay();
        scr = WindowManager::getInstance()->getScreenNum();
        m_root = WindowManager::getInstance()->getRoot();
        m_panelW = GDK_WINDOW_XWINDOW(  GDK_DRAWABLE(this->GetHandle()->window));

        m_selection = WindowManager::getInstance()->getAtom("_NET_SYSTEM_TRAY_S0");
        m_opcode    = WindowManager::getInstance()->getAtom("_NET_SYSTEM_TRAY_OPCODE");
        m_data      = WindowManager::getInstance()->getAtom("_NET_SYSTEM_TRAY_MESSAGE_DATA");


        m_wnd = XCreateSimpleWindow(m_display,m_panelW, x, y+3, width, height, 0,0, WhitePixel(m_display,0));
        XMapRaised(m_display, m_wnd);

        oldOwner = XGetSelectionOwner(m_display, m_selection);
        XSetSelectionOwner(m_display,m_selection, m_wnd, CurrentTime);


        if (XGetSelectionOwner(m_display, m_selection) != m_wnd)
            fprintf(stderr,"could not set selection owner.\nMay be another (greedy) tray running?\n");
        else
            fprintf(stderr, "ok, got _NET_SYSTEM_TRAY selection\n");


        xev.xclient.type       = ClientMessage;
        xev.xclient.serial     = 0;
        xev.xclient.send_event = true;
        xev.xclient.window     = m_root;
        xev.xclient.message_type = XInternAtom (m_display, "MANAGER", false);

        xev.xclient.format    = 32;
        xev.xclient.data.l[0] = CurrentTime;
        xev.xclient.data.l[1] = m_selection;
        xev.xclient.data.l[2] = m_wnd;
        xev.xclient.data.l[3] = 0;	// manager specific data
        xev.xclient.data.l[4] = 0;	// manager specific data

        XSendEvent(m_display, m_root, false, 0xFFFFFF, &xev);

        xa_xembed   = WindowManager::getInstance()->getAtom("_XEMBED");
        m_embedInfo = WindowManager::getInstance()->getAtom("_XEMBED_INFO");
        orientation = WindowManager::getInstance()->getAtom("_NET_SYSTEM_TRAY_ORIENTATION");

        XChangeProperty(m_display, m_wnd, orientation, orientation, 32, PropModeReplace, (unsigned char *) &orient, 1);

        XSelectInput(m_display, m_root, PropertyChangeMask|SubstructureNotifyMask);

        WindowEventManager::getInstance()->addListener(this);
  }


  void TrayPanel::onRawEvent(XEvent &ev)
  {
            if (ev.type == ClientMessage)
            {
               if( ev.xclient.message_type == m_opcode)
                    switch (ev.xclient.data.l[1])
                    {
                         case 0:
                            fprintf(stderr,"dockin requested by %li\n", ev.xclient.data.l[2]);
                            XReparentWindow(m_display, ev.xclient.data.l[2], m_wnd, 0, 0);
                            XMapRaised(m_display,ev.xclient.data.l[2]);
                            m_icons.push_back(ev.xclient.data.l[2]);
                            XSelectInput(m_display,ev.xclient.data.l[2],StructureNotifyMask|PropertyChangeMask);
                            this->layout(0);
                            break;

                          /* We ignore these messages, since we do not show
                           * any baloons anyways */
                           case 1:
                           case 2:
                            break;

                        default:
                         fprintf(stderr,"Unknow dockin requested by %li\n", ev.xclient.data.l[2]);
                         break;
                    }
            }
            else if(ev.type == UnmapNotify )
            {
                if( std::find (m_icons.begin(), m_icons.end(), ev.xunmap.window) != m_icons.end() )
                {
                    fprintf(stderr,"undockin requested by %li\n", ev.xunmap.window);
                    m_icons.remove(ev.xunmap.window);
                    this->layout(ev.xunmap.window);
                }
            }
    }





