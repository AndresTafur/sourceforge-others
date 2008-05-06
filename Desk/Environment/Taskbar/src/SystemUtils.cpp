#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <stdlib.h>


#include "SystemUtils.hh"

		SystemUtils::SystemUtils()
		{
			this->display = GDK_DISPLAY();
			this->scr_num = DefaultScreen(display);
			this->root    = GDK_ROOT_WINDOW();


			m_state    = XInternAtom(display, "_NET_WM_STATE", 0);
			m_skiptask = XInternAtom(display, "_NET_WM_STATE_SKIP_TASKBAR", 0);
			m_totdesk  = XInternAtom(display, "_NET_NUMBER_OF_DESKTOPS", 0);
			m_curdesk  = XInternAtom(display, "_NET_CURRENT_DESKTOP", 0);
			m_deskname = XInternAtom(display, "_NET_DESKTOP_NAMES", 0);
			m_wactive  = XInternAtom(display, "_NET_ACTIVE_WINDOW", 0);
            m_wlist    = XInternAtom(display, "_NET_CLIENT_LIST", 0);
            m_netdesk  = XInternAtom(display, "_NET_WM_DESKTOP",0);
            m_wtype    = XInternAtom(display, "_NET_WM_WINDOW_TYPE", 0);
			m_wnorm    = XInternAtom(display, "_NET_WM_WINDOW_TYPE_NORMAL", 0);
			m_wdlg     = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", 0);
			m_wdock    = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DOCK", 0);
			XSetErrorHandler(SystemUtils::errorHandler);
		}


        int SystemUtils::errorHandler(Display *dsp, XErrorEvent *err)
        {
            fprintf(stderr,"Warning: Xlib error found\n");
            return -1;
        }


		unsigned long SystemUtils::queryManager(Atom property, Atom type, void* data )
		{
			queryManager(root,property,type,data );
		}


		unsigned long SystemUtils::queryManager(Window window,Atom property, Atom type, void* data )
		{
		  int format;
		  unsigned long  num_items = -1;
		  unsigned long  after_bytes;
		  Atom typeret;

                XGetWindowProperty(display,window,property,0,0x7fffffff,0,type,&typeret,
				&format,&num_items,&after_bytes,(unsigned char **)data);

			return num_items;
		}

		void SystemUtils::sendToManager(Atom property,int data1, int data2, int data3, int data4)
		{
			sendToManager(root, property,data1, data2, data3, data4);
		}


		void SystemUtils::sendToManager(Window window, Atom property,int data1, int data2, int data3, int data4)
		{
		   XClientMessageEvent xevent;

			xevent.type         = ClientMessage;
			xevent.window       = window;

			xevent.message_type = property;
			xevent.format = 32;

			xevent.data.l[0]    = data1;
			xevent.data.l[1]    = data2;
			xevent.data.l[2]    = data3;
			xevent.data.l[4]    = data4;

			XSendEvent(display, root, false, SubstructureNotifyMask, (XEvent*)&xevent);
		}



		int SystemUtils::getDesktops()
		{
		  unsigned long *num_desktops;

			queryManager(m_totdesk,XA_CARDINAL,&num_desktops);
			desk_num = (*num_desktops);

            if(num_desktops != NULL)
                XFree(num_desktops);

		return desk_num;
		}


		int SystemUtils::getCurrentDesk()
		{
		  unsigned long *desktop;

	 		 queryManager(m_curdesk,XA_CARDINAL,&desktop);

			curr_desk = (*desktop);

			if(desktop != NULL)
                XFree(desktop);

		return curr_desk;
		}


		Window SystemUtils::getActiveWindow()
		{
		  Window *active, result;
          unsigned long after_bytes;
		  unsigned long num_items;
		  int format;


			queryManager(m_wactive,XA_WINDOW,&active);

			result = (*active);
			if(active != NULL)
                XFree(active);

		  return result;
		}

		char* SystemUtils::getWindowName(Window window)
		{
		  char *name;

                XFetchName(display, window, &name);

		  return name;
		}



		std::list<Window> SystemUtils::getWindows(int *num)
		{
	 	  Window *buff;
	 	  std::list<Window> clients;
		  unsigned long num_item;


			num_item = queryManager(m_wlist,XA_WINDOW,&buff);


			for(int i=0; i < num_item; i++)
				clients.push_front(buff[i]);

		 	*num = clients.size();

            if( buff != NULL)
                XFree(buff);

		  return clients;
		}

		void SystemUtils::setCurrentDesktop(int num)
		{
		    sendToManager( m_curdesk, num, 0, CurrentTime, 0);
		}

		void SystemUtils::setActiveWindow(Window window)
		{
			 sendToManager(window, m_wactive, 0, CurrentTime, 1, 0 );
		}


		int SystemUtils::getWndDesktop(Window window)
		{
			int *states;
			int num = -1;


				if( queryManager(window,m_netdesk,XA_CARDINAL,&states) != -1)
                    num = *states;

		  return num;
		}



		bool SystemUtils::isNormalWnd(Window window)
		{
			Atom *states;
			unsigned long num_items;
			int num;

				num_items = queryManager(window,m_state,XA_ATOM,&states);

                if(states != NULL)
                    for(int i=0; i < num_items; ++i)
                        if(states[i] == m_skiptask)
                        {
                            if(states != NULL)
                                XFree(states);
                            return false;
                        }
		  return true;
		}


        Atom SystemUtils::getAtom(const char *atmnme)
        {
                return XInternAtom(display, atmnme, 0);
        }


		void SystemUtils::iconifyWindow(Window window)
		{
			XIconifyWindow(display, window, scr_num);
		}

		void SystemUtils::closeWindow( Window window)
		{
            sendToManager(window, XInternAtom(display,"_NET_CLOSE_WINDOW",0),time(NULL)-1, 1, 0, 0);
		}

		void SystemUtils::startMoveWindow( Window window)
		{
            sendToManager(window, XInternAtom(display,"_NET_WM_MOVERESIZE",0),0,0,10,0);
		}

		void SystemUtils::startSizeWindow( Window window)
		{
            sendToManager(window, XInternAtom(display,"_NET_WM_MOVERESIZE",0),0,0,9,0);
		}


		unsigned long SystemUtils::screenWidth()
		{
			return XDisplayWidth(display, 0);
		}

		unsigned long SystemUtils::screenHeight()
		{
			return XDisplayHeight(display, 0);
		}

		Atom SystemUtils::getCurrDeskA()
		{
          return m_curdesk;
        }

        Atom SystemUtils::getNetDeskA()
        {
          return m_netdesk;
        }

        Atom SystemUtils::getWindowListA()
        {
          return m_wlist;
        }

        Atom SystemUtils::getActiveWindowA()
        {
          return m_wactive;
        }