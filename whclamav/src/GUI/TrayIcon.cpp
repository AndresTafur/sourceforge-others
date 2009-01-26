#include "TrayIcon.hh"


    MyTaskBarIcon::MyTaskBarIcon(wxWindow *dialog, wxIcon icon)
    {
        m_dialog = dialog;
        m_icon   = icon;
        m_value  = wxT("WhiteHawkAv");
        this->SetIcon(icon,m_value);
    }

    wxString MyTaskBarIcon::getValue()
    {
        return m_value;
    }

    void MyTaskBarIcon::setValue(wxString str)
    {
        m_value  = str;
        this->SetIcon(m_icon,m_value);
    }


    void MyTaskBarIcon::OnLeftButtonDClick(wxTaskBarIconEvent &evt)
    {
        m_dialog->Show(!m_dialog->IsShown());
    }

    void MyTaskBarIcon::OnMenuRestore(wxCommandEvent &evt)
    {
       m_dialog->Show( !m_dialog->IsShown());
    }

    void MyTaskBarIcon::OnMenuExit(wxCommandEvent &evt)
    {
        m_dialog->Destroy();
        this->RemoveIcon();
    }

    wxMenu *MyTaskBarIcon::CreatePopupMenu()
    {
      wxMenu *menu = new wxMenu;

        if(m_dialog->IsShown())
            menu->Append( wxID_PREVIEW, wxT(_("&Hide window")));
        else
            menu->Append( wxID_PREVIEW, wxT( _("&Show window")));
        menu->AppendSeparator();
        menu->Append(wxID_EXIT,wxT( _("&Close")));

      return menu;
    }


BEGIN_EVENT_TABLE(MyTaskBarIcon, wxTaskBarIcon)
    EVT_MENU(wxID_PREVIEW, MyTaskBarIcon::OnMenuRestore)
    EVT_MENU(wxID_EXIT,   MyTaskBarIcon::OnMenuExit)
    EVT_TASKBAR_LEFT_DOWN(MyTaskBarIcon::OnLeftButtonDClick)
END_EVENT_TABLE()
