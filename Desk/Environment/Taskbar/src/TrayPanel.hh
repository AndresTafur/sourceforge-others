#ifndef _TRAY_PANEL_
#define _TRAY_PANEL_

#include <wx/wx.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>


class TrayPanel : public wxPanel
{
public:

	TrayPanel(wxWindow *parent );

    void getSelection();


};
#endif
