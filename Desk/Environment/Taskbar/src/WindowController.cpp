#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <stdlib.h>

#include "WindowManager.hh"
#include "WindowController.hh"

WindowController* WindowController::sm_instance = NULL;


		WindowController::WindowController()
		{
			m_stateA    = WindowManager::getInstance()->getAtom("_NET_WM_STATE");
			m_skiptaskA = WindowManager::getInstance()->getAtom("_NET_WM_STATE_SKIP_TASKBAR");
			m_wactiveA  = WindowManager::getInstance()->getAtom("_NET_ACTIVE_WINDOW");
            m_wlistA    = WindowManager::getInstance()->getAtom("_NET_CLIENT_LIST");

            m_wtypeA    = WindowManager::getInstance()->getAtom("_NET_WM_WINDOW_TYPE");
			m_wnormA    = WindowManager::getInstance()->getAtom("_NET_WM_WINDOW_TYPE_NORMAL");
			m_wdlgA     = WindowManager::getInstance()->getAtom("_NET_WM_WINDOW_TYPE_DIALOG");
			m_wdockA    = WindowManager::getInstance()->getAtom("_NET_WM_WINDOW_TYPE_DOCK");
			m_wcloseA   = WindowManager::getInstance()->getAtom("_NET_CLOSE_WINDOW");
            m_wmoveresA = WindowManager::getInstance()->getAtom("_NET_WM_MOVERESIZE");
		}


        WindowController* WindowController::getInstance()
        {
                if( !sm_instance)
                    sm_instance = new WindowController();
            return sm_instance;
        }



		Window WindowController::getActiveWindow()
		{
		  Window *active, result;
          unsigned long after_bytes;
		  unsigned long num_items;
		  int format;


			WindowManager::getInstance()->queryManager(m_wactiveA,XA_WINDOW,&active);

			result = (*active);
			if(active != NULL)
                XFree(active);

		  return result;
		}

		char* WindowController::getWindowName(Window window)
		{
		  char *name;

                XFetchName(WindowManager::getInstance()->getDisplay(), window, &name);

		  return name;
		}



		std::list<Window> WindowController::getWindows(int *num)
		{
	 	  Window *buff;
	 	  std::list<Window> clients;
		  unsigned long num_item;


			num_item = WindowManager::getInstance()->queryManager(m_wlistA,XA_WINDOW,&buff);


			for(int i=0; i < num_item; i++)
				clients.push_front(buff[i]);

		 	*num = clients.size();

            if( buff != NULL)
                XFree(buff);

		  return clients;
		}



		void WindowController::setActiveWindow(Window window)
		{
			 WindowManager::getInstance()->sendToManager(window, m_wactiveA, 0, CurrentTime, 1, 0 );
		}


		int WindowController::getWndDesktop(Window window)
		{
			int *states;
            int num = -1;
            Atom netdeskA = WindowManager::getInstance()->getAtom("_NET_WM_DESKTOP");

				if( WindowManager::getInstance()->queryManager(window,netdeskA,XA_CARDINAL,&states) != -1)
                    num = *states;

		  return num;
		}



		bool WindowController::isNormalWnd(Window window)
		{
			Atom *states;
			unsigned long num_items;
			int num;

				num_items = WindowManager::getInstance()->queryManager(window,m_stateA,XA_ATOM,&states);

                if(states != NULL)
                    for(int i=0; i < num_items; ++i)
                        if(states[i] == m_skiptaskA)
                        {
                            if(states != NULL)
                                XFree(states);
                            return false;
                        }
		  return true;
		}


		void WindowController::iconifyWindow(Window window)
		{
		   WindowManager *ins = WindowManager::getInstance();
			XIconifyWindow(ins->getDisplay(), window, ins->getScreenNum());
		}

		void WindowController::closeWindow( Window window)
		{
            WindowManager::getInstance()->sendToManager(window,m_wcloseA,time(NULL)-1, 1, 0, 0);
		}

		void WindowController::startMoveWindow( Window window)
		{
            WindowManager::getInstance()->sendToManager(window,m_wmoveresA,0,0,10,0);
		}

		void WindowController::startSizeWindow( Window window)
		{
            WindowManager::getInstance()->sendToManager(window,m_wmoveresA,0,0,9,0);
		}
