
#ifndef _WINDOW_LIST_
#define _WINDOW_LIST_

#include <wx/wx.h>
#include <list>
#include "SystemUtils.hh"
#include "ClientButton.hh"


class WindowList : public wxPanel
{
public:

	WindowList(wxWindow *parent,wxWindowID id, SystemUtils *sysUtils );


	void updateWindows();

	void addWindow(Window window, bool stat);

    void updateWindow(Window window);



    void removeAllMarked();

    void markAllClients();

	void isFull();

	void onClick(wxCommandEvent &evt);

	ClientButton* windowToClient(Window window);

protected:
std::list <ClientButton*> clients;
SystemUtils    *sysUtils;
wxBoxSizer     *sizer;

public:
DECLARE_EVENT_TABLE();
};
#endif
