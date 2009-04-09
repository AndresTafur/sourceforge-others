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


            XSelectInput(dsp, root, PropertyChangeMask|SubstructureNotifyMask);
            XFlush(dsp);



            while(m_run)
            {
                WhiteHawkUtil::Thread::sleep(10);
                while (XPending(dsp))
                {
                    XNextEvent(dsp,&evt);
                    if (evt.type ==  PropertyNotify)
                            onEvent(evt.xany.window,evt.xproperty.atom);
                    else
                            onRawEvent(evt);
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
    }

    void WindowEventManager::onRawEvent(XEvent &evt)
    {
      std::list<WMEventListener*>::iterator iter;

        for( iter = m_listeners.begin(); iter != m_listeners.end(); iter++)
                (*iter)->onRawEvent(evt);
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
