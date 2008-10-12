#include "DeskCtrl.hh"
#include "DeskController.hh"
#include "WindowEventManager.hh"

        DeskCtrl::DeskCtrl(wxWindow *parent) : wxButton(parent,wxID_OK,_T(""),wxDefaultPosition,wxDefaultSize,wxNO_BORDER,wxDefaultValidator,_T(""))
        {
          wxMenuItem **items;
          int desks;


                desks  = DeskController::getInstance()->getDesktops();
                items  = (wxMenuItem**) malloc( sizeof(wxMenuItem)*desks);
                m_menu = new wxMenu;


                for(int i=0; i < desks; i++)
                {
                    items[i] = new wxMenuItem(m_menu,i,(wxString("Desk ")) << (char)(49+i),wxT(""),wxITEM_RADIO);
                    m_menu->Append(items[i]);
                    Connect(i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(DeskCtrl::changeDesktop));
                }

                this->SetLabel(  (wxString("")) << (char)(49+DeskController::getInstance()->getCurrentDesk()) );
                this->SetBackgroundColour("LIGHT STEEL BLUE");
                this->SetSize(20,25);
                this->SetFont( wxFont(8,wxFONTFAMILY_DEFAULT,0,wxFONTWEIGHT_BOLD,false,"",wxFONTENCODING_DEFAULT));
                this->SetToolTip("Cambia el escritorio actual");

                WindowEventManager::getInstance()->addListener(this);
        }


        void DeskCtrl::onEvent(Window &wnd,Atom &atom)
        {
              if(wnd == WindowManager::getInstance()->getRoot() && atom == WindowManager::getInstance()->getAtom("_NET_CURRENT_DESKTOP"))
                {
                  unsigned short curdesk = DeskController::getInstance()->getCurrentDesk() + 1;
                  wxString str("");

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
            DeskController::getInstance()->showDesktop(true);
        }



BEGIN_EVENT_TABLE(DeskCtrl,wxButton)
EVT_BUTTON(wxID_OK,DeskCtrl::showDesktop)
EVT_RIGHT_DOWN(DeskCtrl::showDeskSelector)
END_EVENT_TABLE()
