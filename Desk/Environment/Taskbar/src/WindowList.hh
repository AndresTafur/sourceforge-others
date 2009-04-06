
#ifndef _WINDOW_LIST_
#define _WINDOW_LIST_

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <list>
#include "WindowController.hh"
#include "ClientButton.hh"
#include "WMEventListener.hh"


class WindowList : public wxPanel, public WMEventListener
{
public:

	WindowList(wxWindow *parent,wxWindowID id);

	void updateWindows();

    void onEvent(Window wnd, Atom atom);

	void addWindow(Window window, bool stat);

    void updateWindow(Window window);

    void removeAllMarked();

    void markAllClients();

	void onClick(wxCommandEvent &evt);

	void about(wxCommandEvent &evt);

    void showOptions(wxMouseEvent &evt);

	ClientButton* windowToClient(Window window);

protected:
std::list <ClientButton*> clients;
wxBoxSizer     *sizer;

public:
DECLARE_EVENT_TABLE();
};
#endif
