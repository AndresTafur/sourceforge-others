#include "WMManager.hh"
#include "WMInstance.hh"


            WMManager::WMManager() : Thread()
            {
                this->m_run      = true;
            }

            void WMManager::ThreadRoutine()
            {
              XEvent evt;

                XSelectInput(WMInstance::getDisplay(),WMInstance::getRoot(),
                    SubstructureNotifyMask | FocusChangeMask | PropertyChangeMask | ExposureMask);
                XFlush(WMInstance::getDisplay());

                while(m_run)
                {
                    usleep(200);
                    while (XPending(WMInstance::getDisplay()))
                    {
                        XNextEvent(WMInstance::getDisplay(),&evt);

                        switch (evt.type)
                        {
                            case PropertyNotify:
                                propagateEvent( WMEvent(evt.xproperty.window,evt.xproperty.atom,XGetAtomName(WMInstance::getDisplay(),evt.xproperty.atom)));
                                break;

                            case Expose:
                                propagateEvent( WMEvent(evt.xexpose.window));
                                break;

                            case DestroyNotify:
                                propagateEvent( WMEvent(evt.xdestroywindow.window));
                                break;

                            case ClientMessage:
                                propagateEvent( WMEvent(evt.xclient.window));
                                break;

                            case ConfigureNotify:
                                propagateEvent( WMEvent(evt.xconfigure.window));
                                break;

                            case MapNotify:
                                propagateEvent( WMEvent(evt.xmap.window));
                                break;

                            case UnmapNotify:
                                propagateEvent( WMEvent(evt.xunmap.window));
                                break;

                            case ReparentNotify:
                                propagateEvent( WMEvent(evt.xreparent.window));
                                break;
                      }
                    }
                }
            }

            void WMManager::addListener(WMListener *listener)
            {
                m_handlers.push_back(listener);
            }

            void WMManager::removeListener(WMListener *listener)
            {
                m_handlers.remove(listener);
            }

            void WMManager::propagateEvent(WMEvent evt)
            {
              std::list<WMListener*>::iterator iter = m_handlers.begin();

                for( ;iter != m_handlers.end(); iter++)
                    (*iter)->onEvent(evt);
            }

            void WMManager::onTerminate()
            {}
