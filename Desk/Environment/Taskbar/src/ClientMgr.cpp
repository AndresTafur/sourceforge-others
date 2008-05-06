#include "ClientMgr.hh"



    ClientMgr::ClientMgr(SystemUtils *sysUtils )
	{
		this->sysUtils = sysUtils;
		this->updateWindows();
	}


    ClientMgr::updateWindows()
    {
      std::list<Window> windows;
	  std::list<Window>::iterator iter;
	  Window act;
	  int num, desknum, i=0;

		 windows = sysUtils->getWindows(&num);
		 act 	 = sysUtils->getActiveWindow();
		 desknum = sysUtils->getCurrentDesk();

         this->markAllClients();

        if( windows.size() > 0)
            for(iter = windows.begin(); i < num; i++, ++iter)
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


    }
