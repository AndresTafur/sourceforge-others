#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include "rcids.h"
#include "AvNotebook.h"
#include <wx/taskbar.h>

#ifndef _AVFRAME_H_
#define _AVFRAME_H_


class AvFrame : public wxFrame
{
public:


    AvFrame(wxString path);


    void createMenu();

    void createTrayIcon();

    void onTaskClick(wxTaskBarIconEvent &evt);

    void onTaskLClick(wxTaskBarIconEvent &evt);

    void onHome(wxCommandEvent &evt);

    void onScan(wxCommandEvent &evt);

    void onQuit(wxCommandEvent &evt);

    void onAbout(wxCommandEvent &evt);


protected:
wxBoxSizer  *sizer;
wxPanel	    *current;
AvNotebook  *note;
StatusPanel *status;
wxIcon      *icon;
wxMenu      *trayMenu;

DECLARE_EVENT_TABLE()

};

#endif
