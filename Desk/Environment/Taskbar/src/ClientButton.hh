
#ifndef _CLIENT_BUTTON_
#define _CLIENT_BUTTON_


#include <wx/tglbtn.h>
#include <X11/Xlib.h>
#include "WindowController.hh"
#include "DeskController.hh"

class ClientButton : public wxToggleButton
{
public:

    ClientButton(wxWindow* parent,wxWindowID id, Window window, wxString label);


	void AddToTaskbar();

    void setMark(bool mark);

    void updateName();

    wxString GetRealName();

	Window GetXWindow();

    void CloseXWindow();

    bool isMarked();

	void onRightClick(wxMouseEvent &evt);

	void onDeskChange(wxCommandEvent &evt);

	void Maximize(wxCommandEvent &evt);

	void Minimize(wxCommandEvent &evt);

    void CloseWnd(wxCommandEvent &evt);

    void StartMoving(wxCommandEvent &evt);

    void StartResizing(wxCommandEvent &evt);


protected:
wxMenu *m_menu;
wxMenu *m_desk;
wxString m_label;
Window   m_xwindow;
bool m_marked;
DECLARE_EVENT_TABLE()
};

#endif
