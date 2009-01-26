#ifndef _TRAYICON_HH_
#define _TRAYICON_HH_

#include <wx/wx.h>
#include <wx/taskbar.h>

#include "../config.h"
#include "ClamLayer/ClamavInstance.hh"

class MyTaskBarIcon: public wxTaskBarIcon
{
public:

    MyTaskBarIcon(wxWindow *dialog, wxIcon icon);

    wxString getValue();

    void setValue(wxString str);

    void OnLeftButtonDClick(wxTaskBarIconEvent&);

    void OnMenuRestore(wxCommandEvent&);

    void OnMenuExit(wxCommandEvent&);

    virtual wxMenu *CreatePopupMenu();


protected:
wxWindow *m_dialog;
wxIcon    m_icon;
wxString  m_value;
DECLARE_EVENT_TABLE()
};
#endif
