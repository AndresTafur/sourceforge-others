#include "DeskCtrl.hh"



        DeskCtrl::DeskCtrl(wxWindow *parent) : wxButton(parent,wxID_OK,wxT(""),wxDefaultPosition,wxDefaultSize,wxNO_BORDER)
        {
          wxMenuItem **items;
          int desks;
          wxString deskBuff;


                desks  = DeskController::getInstance()->getDesktops();
                items  = (wxMenuItem**) new wxMenuItem[desks];
                m_menu = new wxMenu;


                for(int i=0; i < desks; i++)
                {
                    deskBuff << wxT("Desk ") << wxString::FromAscii(char(49+i));
                    items[i] = new wxMenuItem( m_menu,i,deskBuff,wxT(""),wxITEM_RADIO);
                    m_menu->Append(items[i]);
                    Connect(i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(DeskCtrl::changeDesktop));
                    deskBuff = wxT("");
                }

                deskBuff << wxT("") <<  DeskController::getInstance()->getCurrentDesk()+1;
                this->SetLabel(deskBuff);
                this->SetBackgroundColour( wxT("LIGHT STEEL BLUE"));
                this->SetSize(20,25);
                this->SetFont( wxFont(8,wxFONTFAMILY_DEFAULT,0,wxFONTWEIGHT_BOLD,false,wxT(""),wxFONTENCODING_DEFAULT));
                this->SetToolTip(wxT("Cambia el escritorio actual"));

                WindowEventManager::getInstance()->addListener(this);
        }


        void DeskCtrl::onEvent(Window wnd,Atom atom)
        {
              if(wnd == WindowManager::getInstance()->getRoot() && atom == WindowManager::getInstance()->getAtom("_NET_CURRENT_DESKTOP"))
                {
                  unsigned short curdesk = DeskController::getInstance()->getCurrentDesk() + 1;
                  wxString str(wxT(""));

                    str << curdesk;
                    wxMutexGuiEnter();
                    this->SetLabel(str);
                    m_menu->Check(curdesk-1,true);
                    this->Update();
                    wxMutexGuiLeave();
                }
        }


        void DeskCtrl::changeDesktop(wxCommandEvent &evt)
        {
            m_deskNum = evt.GetId();
            DeskController::getInstance()->setCurrentDesktop(m_deskNum);
        }


        void DeskCtrl::showDeskSelector(wxMouseEvent &evt)
        {
            this->PopupMenu(m_menu,0,0);
        }

        void DeskCtrl::showDesktop(wxCommandEvent &evt)
        {
            DeskController *dskctr =  DeskController::getInstance();

                DeskController::getInstance()->showDesktop(  !dskctr->isVisible() );
        }



BEGIN_EVENT_TABLE(DeskCtrl,wxButton)
EVT_BUTTON(wxID_OK,DeskCtrl::showDesktop)
EVT_RIGHT_DOWN(DeskCtrl::showDeskSelector)
END_EVENT_TABLE()

