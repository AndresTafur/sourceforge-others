#include "WindowEventManager.hh"
#include <X11/Xatom.h>
#include <stdlib.h>

    WindowEventManager::WindowEventManager(SystemUtils *sysUtils, TaskBar *bar)
    {
         this->m_run      = true;
         this->m_sysUtils = sysUtils;
         this->m_list     = bar->getWndListPanel();
         this->m_dsp      = XOpenDisplay(NULL);
         this->m_root     = XDefaultRootWindow(m_dsp);
         this->m_bar      = bar;
    }


    void WindowEventManager::ThreadRoutine()
    {
       XEvent evt;

			XSelectInput(m_dsp,m_root,StructureNotifyMask | FocusChangeMask | PropertyChangeMask | ExposureMask);
            XFlush(m_dsp);

            while(m_run)
            {
                usleep(200);
                while (XPending(m_dsp))
                {
                    XNextEvent(m_dsp,&evt);

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

    void WindowEventManager::onTerminate()
    {}


    void WindowEventManager::onEvent(Window window,Atom atom)
    {
           if(window == m_root)
            {
                if (atom == m_sysUtils->getWindowListA())
                {
                  wxMutexGuiEnter();
                  m_list->updateWindows();
                  wxMutexGuiLeave();
                  return;
                }
                else if( atom == m_sysUtils->getCurrDeskA())
                {
                  unsigned short curdesk = m_sysUtils->getCurrentDesk() + 1;

                  wxMutexGuiEnter();
                  m_list->updateWindows();
                  m_bar->onChangeDesk(curdesk);
                  wxMutexGuiLeave();
                  return;
                }

            }



            if (atom == XA_WM_NAME ) //TODO: Makes this fu.... thing works
            {/*
                  wxMutexGuiEnter();
                 // m_list->updateWindows();
                  wxMutexGuiLeave();*/
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
