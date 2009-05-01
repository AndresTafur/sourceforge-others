
#ifndef _CLIENT_BUTTON_
#define _CLIENT_BUTTON_


#include <wx/tglbtn.h>
#include <wx/dnd.h>
#include <wx/tooltip.h>
#include <wx/wx.h>
#include <wx/timer.h>

#include <X11/Xlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#include "WindowController.hh"
#include "WindowManager.hh"
#include "DeskController.hh"



enum
{
    MINIMIZE,
    MAXIMIZE,
    START_MOVING,
    START_RESIZING,
    DESKTOP_1,
};


class DragController : public wxTimer, public wxDropTarget
{
public:
        void Notify();

        void setWindow(Window wnd){ m_wnd = wnd;}

        bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString&);

        wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def);

        void OnLeave();

private:
Window m_wnd;
};


class ClientButton : public wxToggleButton
{
public:

    ClientButton(wxWindow* parent,wxWindowID id, Window window);

    void setMark(bool mark);

    void updateName();

    wxString GetRealName();

	Window GetXWindow();


    void CloseXWindow();

    void Maximize(wxCommandEvent &evt);

	void Minimize(wxCommandEvent &evt);

    void CloseWnd(wxCommandEvent &evt);

    void StartMoving(wxCommandEvent &evt);

    void StartResizing(wxCommandEvent &evt);



    bool isMarked();

	void onRightClick(wxMouseEvent &evt);

	void onDeskChange(wxCommandEvent &evt);



private:
wxMenu *m_menu;
wxMenu *m_desk;
wxString m_label;
Window   m_xwindow;
DragController *m_ctrl;
bool m_marked;
DECLARE_EVENT_TABLE()
};

#endif

