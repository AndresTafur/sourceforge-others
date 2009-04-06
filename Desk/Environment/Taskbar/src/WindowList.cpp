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

                                XSelectInput(WindowManager::getInstance()->getDisplay(),*iter,PropertyChangeMask);
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
        else if( atom == WindowManager::getInstance()->getAtom("_NET_WM_NAME"))
        {
          ClientButton *button = windowToClient(wnd);

            if( NULL !=  button)
            {
                  wxMutexGuiEnter();
                  button->updateName();
                  this->Layout();
                  this->Update();
                  wxMutexGuiLeave();
            }
        }
       else if(wnd == WindowManager::getInstance()->getRoot() )
               if(atom == WindowManager::getInstance()->getAtom("_NET_CLIENT_LIST"))
               {
                  wxMutexGuiEnter();
                  this->updateWindows();
                  this->Layout();
                  this->Update();
                  wxMutexGuiLeave();
               }
    }

	void WindowList::addWindow(Window window, bool stat)
	{
        if( window)
            if(WindowController::getInstance()->isNormalWnd(window) )
            {

              ClientButton *item = new ClientButton(this,100,window,wxString::FromAscii(WindowController::getInstance()->getWindowName(window)));

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

    void WindowList::showOptions(wxMouseEvent &evt)
    {
      wxMenu menu;

            menu.Append(wxID_PREFERENCES, wxT("Propiedades"), wxT("Propiedades"), wxITEM_NORMAL);
            menu.Append(wxID_HELP, wxT("Ayuda"), wxT("Ayuda"), wxITEM_NORMAL);
            menu.AppendSeparator();
            menu.Append(wxID_ABOUT, wxT("Acerca de"), wxT("Acerca de"), wxITEM_NORMAL);
            PopupMenu(&menu);
    }



    void WindowList::about(wxCommandEvent &evt)
    {
      wxAboutDialogInfo info;

        info.SetName( wxT("WhitehawkPanel"));
        info.SetVersion( wxT("0.1.0"));
        info.SetDescription(wxT("\n\nWelcome to WhiteHawk Desk panel."));
        info.SetWebSite( wxT("http://whsystems.sf.net"));
        info.SetCopyright( wxT("Copyright (C) 2007 WhiteHawk project."));
        info.AddDeveloper( wxT("Jorge Andres Tafur"));
        info.SetLicence( wxT

        ("\tWhiteHawkDeskPanel a toolbar based on top of X11.\n"
                  "\t\t\tCopyright (C) 2007  Jorge andres tafur\n\n\n"

        "This program is free software: you can redistribute it and/or modify\n"
        "it under the terms of the GNU General Public License as published by\n"
        "the Free Software Foundation, either version 3 of the License, or\n"
        "any later version.\n\n"

        "This program is distributed in the hope that it will be useful,\n"
        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
        "GNU General Public License for more details.\n\n"

        "You should have received a copy of the GNU General Public License\n"
        "along with this program.  If not, see http://www.gnu.org/licenses/.")
    );

    wxAboutBox(info);

    }


BEGIN_EVENT_TABLE(WindowList,wxPanel)
EVT_TOGGLEBUTTON(100,WindowList::onClick)
EVT_RIGHT_UP(WindowList::showOptions)
EVT_MENU(wxID_ABOUT,WindowList::about)
END_EVENT_TABLE()
