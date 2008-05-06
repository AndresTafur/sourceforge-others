

#ifndef _CLIENT_MGR_HH
#define _CLIENT_MGR_HH


class ClientMgr
{
public:


    ClientMgr(SystemUtils *sysUtils );

    updateWindows();

    void markAllClients();

    ClientButton* windowToClient(Window window);

    void WindowList::removeAllMarked();

    updateWindow(Window window);

    addWindow(Window window, bool stat);

    virtual void onUpdateWindows();

};


#endif

