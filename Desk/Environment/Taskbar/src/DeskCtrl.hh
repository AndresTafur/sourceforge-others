#ifndef _DESK_CTRL_
#define _DESK_CTRL_

#include <wx/wx.h>
#include "WMEventListener.hh"

class DeskCtrl : public wxButton, public WMEventListener
{
public:

        DeskCtrl(wxWindow *parent);

        void onEvent(Window wnd, Atom atom);

        void changeDesktop(wxCommandEvent &evt);

        void showDeskSelector(wxMouseEvent &evt);

        void showDesktop(wxCommandEvent &evt);

protected:
wxMenu *m_menu;
int m_deskNum;
DECLARE_EVENT_TABLE();
};

#endif
