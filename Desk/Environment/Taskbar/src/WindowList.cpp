#include "WindowList.hh"
#include "WindowEventManager.hh"


	WindowList::WindowList(wxWindow *parent,wxWindowID id) : wxPanel(parent,id,wxDefaultPosition,wxDefaultSize, wxCLIP_CHILDREN|wxTAB_TRAVERSAL)
	{
		sizer = new wxBoxSizer(wxHORIZONTAL);

        WindowEventManager::getInstance()->addListener(this);

    	this->SetSizer(sizer);
		this->updateWindows();
	}



	void WindowList::updateWindows()
	{
	  std::list<Window> windows;
	  std::list<Window>::iterator iter;
	  Window act;
	  int num, desknum, i=0;


		 desknum = DeskController::getInstance()->getCurrentDesk();
         windows = WindowController::getInstance()->getWindows(&num);
		 act 	 = WindowController::getInstance()->getActiveWindow();


         this->markAllClients();


        if( windows.size() > 0)
            for(iter = windows.begin(); i != num; i++, ++iter)
              if(*iter)
                if( WindowController::getInstance()->getWndDesktop(*iter) == desknum )
                    {
                        ClientButton *button = windowToClient(*iter);

                        if( button == NULL)
                        {
                            if( act == *iter)
                                addWindow(*iter, true);
                            else
                                addWindow(*iter, false);
                        }
                        else
                            button->setMark(false);
                    }

         this->removeAllMarked();
         this->Update();
		 this->Layout();
	}


    void WindowList::onEvent(Window wnd, Atom atom)
    {

        if( atom == WindowManager::getInstance()->getAtom("_NET_ACTIVE_WINDOW"))
        {
            wxMutexGuiEnter();
            updateWindow(WindowController::getInstance()->getActiveWindow());
            this->Update();
            wxMutexGuiLeave();
        }
        else if(wnd == WindowManager::getInstance()->getRoot() )
               if(atom == WindowManager::getInstance()->getAtom("_NET_CLIENT_LIST"))
               {
                  wxMutexGuiEnter();
                  this->updateWindows();
                  wxMutexGuiLeave();
               }
    }

	void WindowList::addWindow(Window window, bool stat)
	{
        if( window)
            if(WindowController::getInstance()->isNormalWnd(window) )
            {

              ClientButton *item = new ClientButton(this,100,window,WindowController::getInstance()->getWindowName(window));

                item->SetValue(stat);
                clients.push_back(item);
                this->Update();
                this->Layout();
            }
	}


    void WindowList::updateWindow(Window window)
	{
        if(window)
        {
           ClientButton *button = windowToClient(window);


                if( NULL != button )
                {

                    for( std::list<ClientButton*>::iterator i=clients.begin(); i != clients.end(); ++i)
                    {
                            if( NULL != (*i) )
                             (*i)->SetValue(false);
                    }
                    button->SetValue(true);
                    this->Update();
                    this->Layout();
                }
        }
	}

    void WindowList::removeAllMarked()
	{
            if( clients.size() > 0)
            {
                for( std::list<ClientButton*>::iterator i=clients.begin(); i != clients.end(); ++i)
                {
                    if(*i)
                        if( (*i)->isMarked())
                        {
                            clients.erase(i);
                            sizer->Remove(*i);
                            (*i)->Destroy();
                            i=clients.begin();
                        }
                }
                this->Layout();
            }
    }

    void WindowList::markAllClients()
	{
            if( clients.size() > 0)
                for( std::list<ClientButton*>::iterator i=clients.begin(); i != clients.end(); ++i)
                    if(*i)
                       (*i)->setMark(true);
    }


    ClientButton* WindowList::windowToClient(Window window)
    {
         for( std::list<ClientButton*>::iterator i=clients.begin(); i != clients.end(); ++i)
                if((*i)->GetXWindow() == window)
                    return (*i);
        return NULL;
    }

	void WindowList::onClick(wxCommandEvent &evt)
	{
	  ClientButton *button = (ClientButton*)evt.GetEventObject();

		if( button)
		{
			if(button->GetValue())
			{
				for(std::list<ClientButton*>::iterator i=clients.begin(); i != clients.end(); ++i)
					(*i)->SetValue(false);

				button->SetValue(true);
				WindowController::getInstance()->setActiveWindow(button->GetXWindow());
			}
			else
			  WindowController::getInstance()->iconifyWindow(button->GetXWindow());
		}
	}



BEGIN_EVENT_TABLE(WindowList,wxPanel)
EVT_TOGGLEBUTTON(100,WindowList::onClick)
END_EVENT_TABLE()
