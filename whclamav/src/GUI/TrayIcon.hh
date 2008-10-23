#ifndef _TRAYICON_HH_
#define _TRAYICON_HH_

#include <wx/wx.h>
#include <wx/taskbar.h>

class MyTaskBarIcon: public wxTaskBarIcon
{
public:

    MyTaskBarIcon(wxWindow *dialog);

    void OnLeftButtonDClick(wxTaskBarIconEvent&);

    void OnMenuRestore(wxCommandEvent&);

    void OnMenuExit(wxCommandEvent&);

    virtual wxMenu *CreatePopupMenu();


protected:
wxWindow *dialog;
DECLARE_EVENT_TABLE()
};
#endif
