#ifndef _DOCK_PANEL_
#define _DOCK_PANEL_

#include <wx/frame.h>


class DockPanel : public wxFrame
{
public:

     DockPanel(wxPoint position,wxSize size, wxString title = wxT("Dock") );

     void setDockable();

     void setAsTaskbar();

};

#endif

