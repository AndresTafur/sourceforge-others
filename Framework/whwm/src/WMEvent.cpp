  #include "WMEvent.hh"


        WMEvent::WMEvent(Window window,int evtType,std::string name)
        {
            this->m_evtType = evtType;
            this->m_window  = window;
            this->m_name    = name;
        }

        void WMEvent::setEvtType(int evtType)
        {
            this->m_evtType = evtType;
        }

        void WMEvent::setEvtName(std::string name)
        {
            this->m_name = name;
        }

        void WMEvent::setWindow(Window window)
        {
            this->m_window = window;
        }

