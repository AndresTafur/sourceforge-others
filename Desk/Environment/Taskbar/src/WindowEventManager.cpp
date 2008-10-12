#include "WindowEventManager.hh"
#include <X11/Xatom.h>
#include <stdlib.h>

WindowEventManager *WindowEventManager::sm_instance = NULL;


    WindowEventManager::WindowEventManager()
    {
        m_run = true;
    }


    WindowEventManager* WindowEventManager::getInstance()
    {
            if(!sm_instance)
             sm_instance = new WindowEventManager();
        return sm_instance;
    }


    void WindowEventManager::run()
    {
       XEvent evt;
       Window root = WindowManager::getInstance()->getRoot();
       Display *dsp = WindowManager::getInstance()->getDisplay();

			XSelectInput(dsp,root,StructureNotifyMask | FocusChangeMask | PropertyChangeMask | ExposureMask);
            XFlush(dsp);



            while(m_run)
            {
                usleep(200);
                while (XPending(dsp))
                {
                    XNextEvent(dsp,&evt);

                    switch (evt.type)
                    {
                        case PropertyNotify:
                            onEvent(evt.xproperty.window,evt.xproperty.atom);
                        break;

                        case Expose:
                          fprintf(stderr,"EXPOSURE\n");
                        break;

                        case DestroyNotify:
                        fprintf(stderr,"DESTROY\n");
                        break;

                        case ClientMessage:
                        fprintf(stderr,"MESSAGE\n");
                        break;


                        case ConfigureNotify:
                        fprintf(stderr,"CONFIGURE\n");
                        break;

                        case MapNotify:
                        fprintf(stderr,"MAP\n");
                        break;

                        case ReparentNotify:
                        fprintf(stderr,"REPARENT\n");
                        break;
                    }

                 }

            }
    }

    void WindowEventManager::addListener( WMEventListener *list)
    {
        m_listeners.push_back(list);
    }

    void WindowEventManager::removeListener( WMEventListener *list)
    {
        m_listeners.remove(list);
    }

    void WindowEventManager::onEvent(Window window,Atom atom)
    {
      std::list<WMEventListener*>::iterator iter;


        for( iter = m_listeners.begin(); iter != m_listeners.end(); iter++)
                (*iter)->onEvent(window,atom);

/*

            if (atom == XA_WM_NAME ) //TODO: Makes this fu.... thing works
            {/*
                  wxMutexGuiEnter();
                 // m_list->updateWindows();
                  wxMutexGuiLeave();
            }
            if (atom == m_sysUtils->getActiveWindowA())
            {
                  wxMutexGuiEnter();
                  m_list->updateWindow(  m_sysUtils->getActiveWindow() );
                  wxMutexGuiLeave();
            }
          /*else if (atom == XA_WM_HINTS)
            {
                //TODO: Icon Loading

            }*/

    }


    void WindowEventManager::onTerminate()
    {

    }
