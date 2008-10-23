#include "TrayIcon.hh"


    MyTaskBarIcon::MyTaskBarIcon(wxWindow *dialog)
    {
        this->dialog = dialog;
    }

    void MyTaskBarIcon::OnLeftButtonDClick(wxTaskBarIconEvent &evt)
    {
        dialog->Show( !dialog->IsShown());
    }

    void MyTaskBarIcon::OnMenuRestore(wxCommandEvent &evt)
    {
       dialog->Show( !dialog->IsShown());
    }

    void MyTaskBarIcon::OnMenuExit(wxCommandEvent &evt)
    {
        dialog->Destroy();
        this->RemoveIcon();
    }

    wxMenu *MyTaskBarIcon::CreatePopupMenu()
    {
      wxMenu *menu = new wxMenu;

        if(dialog->IsShown())
            menu->Append( wxID_PREVIEW, wxT("&Hide window"));
        else
            menu->Append( wxID_PREVIEW, wxT("&Show window"));
        menu->AppendSeparator();
        menu->Append(wxID_EXIT,wxT("&Close"));

      return menu;
    }


BEGIN_EVENT_TABLE(MyTaskBarIcon, wxTaskBarIcon)
    EVT_MENU(wxID_PREVIEW, MyTaskBarIcon::OnMenuRestore)
    EVT_MENU(wxID_EXIT,   MyTaskBarIcon::OnMenuExit)
    EVT_TASKBAR_LEFT_DOWN(MyTaskBarIcon::OnLeftButtonDClick)
END_EVENT_TABLE()
