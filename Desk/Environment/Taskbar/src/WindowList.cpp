#include "WindowList.hh"



	WindowList::WindowList(wxWindow *parent,wxWindowID id, SystemUtils *sysUtils ) : wxPanel(parent,id,wxDefaultPosition,wxDefaultSize, wxCLIP_CHILDREN|wxTAB_TRAVERSAL)
	{
		sizer = new wxBoxSizer(wxHORIZONTAL);

		this->sysUtils = sysUtils;
		this->SetSizer(sizer);
		this->updateWindows();
	}



	void WindowList::updateWindows()
	{
	  std::list<Window> windows;
	  std::list<Window>::iterator iter;
	  Window act;
	  int num, desknum, i=0;


		 desknum = sysUtils->getCurrentDesk();
         windows = sysUtils->getWindows(&num);
		 act 	 = sysUtils->getActiveWindow();


         this->markAllClients();


        if( windows.size() > 0)
            for(iter = windows.begin(); i != num; i++, ++iter)
              if(*iter)
                if( sysUtils->getWndDesktop(*iter) == desknum )
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
		isFull();
	}


	void WindowList::addWindow(Window window, bool stat)
	{
        if( window)
            if(sysUtils->isNormalWnd(window) )
            {

              ClientButton *item = new ClientButton(this,100,window,sysUtils->getWindowName(window),sysUtils);

                item->SetValue(stat);
                clients.push_back(item);
                isFull();
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
                    isFull();
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


	void WindowList::isFull()
	{
	     this->Update();
		 this->Layout();
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
				sysUtils->setActiveWindow(button->GetXWindow());
			}
			else
			{
			  sysUtils->iconifyWindow(button->GetXWindow());
			}
		}
	}



BEGIN_EVENT_TABLE(WindowList,wxPanel)
EVT_TOGGLEBUTTON(100,WindowList::onClick)
END_EVENT_TABLE()
