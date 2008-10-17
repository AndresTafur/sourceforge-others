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

			XSelectInput(dsp,root,StructureNotifyMask|PropertyChangeMask|SubstructureNotifyMask);
            XFlush(dsp);



            while(m_run)
            {
                usleep(20);
                while (XPending(dsp))
                {
                    XNextEvent(dsp,&evt);

                    fprintf(stderr,"[Event reached]\n");

                    if (evt.type ==  PropertyNotify)
                            onEvent(evt.xany.window,evt.xproperty.atom);
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


            if (atom == XA_WM_NAME ) //TODO: Makes this fu.... thing works
            {
                printf("[Name changed]\n");
             /*
                  wxMutexGuiEnter();
                 // m_list->updateWindows();
                  wxMutexGuiLeave();*/
            }/*

          /*else if (atom == XA_WM_HINTS)
            {
                //TODO: Icon Loading

            }*/
    }


    void WindowEventManager::onTerminate()
    {

    }


    void WindowEventManager::destroy()
    {
        delete sm_instance;
    }

    WindowEventManager::~WindowEventManager()
    {
        //
    }
