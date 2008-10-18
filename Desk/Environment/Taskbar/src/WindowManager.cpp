#include "WindowManager.hh"


WindowManager *WindowManager::sm_instance = NULL;


   WindowManager::WindowManager()
   {
			XSetErrorHandler(WindowManager::errorHandler);

            m_display = XOpenDisplay(NULL);
            m_scrNum  = DefaultScreen(m_display);
            m_root    = XDefaultRootWindow(m_display);

            if(!m_display)
                fprintf(stderr,"FAILED TO OPEN DISPLAY");
   }



   int WindowManager::errorHandler(Display *dsp, XErrorEvent *err)
   {
      char buffer_return[100];

            XGetErrorText(WindowManager::getInstance()->getDisplay(), err->error_code, buffer_return, 100);


            fprintf(stderr,"Warning Xlib error found: %s\n",buffer_return);
            return -1;
   }

   WindowManager* WindowManager::getInstance()
   {
        if( !sm_instance)
            sm_instance = new WindowManager();
     return sm_instance;

   }


   unsigned long WindowManager::queryManager(Atom &property, Atom type, void* data )
   {
		queryManager(m_root,property,type,data );
   }


   unsigned long WindowManager::queryManager(Window &window,Atom &property, Atom type, void* data )
   {
	  int format;
	  unsigned long  num_items = -1;
	  unsigned long  after_bytes;
	  Atom typeret;

           XGetWindowProperty(m_display,window,property,0,0x7fffffff,0,type,&typeret,
				&format,&num_items,&after_bytes,(unsigned char **)data);

			return num_items;
	}

	void WindowManager::sendToManager(Atom &property,int data1, int data2, int data3, int data4)
	{
           sendToManager(m_root, property,data1, data2, data3, data4);
	}


    void WindowManager::sendToManager(Window window, Atom property,int data1, int data2, int data3, int data4)
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


			XSendEvent(m_display, m_root, false, SubstructureNotifyMask, (XEvent*)&xevent);
			XFlush(m_display);
		}



    Atom WindowManager::getAtom(std::string atName)
    {
       return XInternAtom(m_display, atName.c_str(),false);
    }


    unsigned long WindowManager::screenWidth()
	{
			return XDisplayWidth(m_display, m_scrNum);
	}

	unsigned long WindowManager::screenHeight()
	{
			return XDisplayHeight(m_display, m_scrNum);
	}

    Display* WindowManager::getDisplay()
    {
            return m_display;
    }

    int WindowManager::getScreenNum()
    {
        return m_scrNum;
    }

    Window WindowManager::getRoot()
    {
        return m_root;
    }


    void WindowManager::destroy()
    {
       delete sm_instance;
    }


    WindowManager::~WindowManager()
    {
        XCloseDisplay(m_display);
    }
