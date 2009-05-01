
#ifndef _TRAY_PANEL_
#define _TRAY_PANEL_

#include <stdio.h>
#include <list>
#include <algorithm>


#include <wx/wx.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <Thread.hh>

#include "../WindowManager.hh"
#include "../WMEventListener.hh"


class TrayPanel : public wxPanel, public WMEventListener
{
public:

	TrayPanel(wxWindow *parent);

    void onEvent(Window wnd, Atom atom);

    void layout(Window wnd);

    void getSelection();

    virtual void onRawEvent(XEvent &ev);


private:
std::list<Window> m_icons;
Display *m_display;
Atom m_selection;
Atom m_opcode;
Atom m_data;
Atom m_embedInfo;
Window m_wnd;
Window m_panelW;
Window m_root;
int m_x;
int m_y;
int m_width, m_height;

};

#endif
