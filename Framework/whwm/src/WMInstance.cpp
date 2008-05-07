#include "WMInstance.hh"

Display   *WMInstance::m_dsp  = XOpenDisplay(0);
WMInput   *WMInstance::m_in   = new WMInput();
WMOutput  *WMInstance::m_out  = new WMOutput();
WMManager *WMInstance::m_mgr  = new WMManager();
Window     WMInstance::m_root = 0;


            WMInstance::WMInstance(){ }


            void  WMInstance::init()
            {
                    m_mgr->Create();
            }


            Display*   WMInstance::getDisplay()
            {
                    if( m_dsp == NULL)
                        m_dsp = XOpenDisplay(0);
                return m_dsp;
            }

            Window   WMInstance::getRoot()
            {
                if( m_root == 0)
                    m_root = XRootWindow(m_dsp,0);
                return m_root;
            }

            WMInput*  WMInstance::getInput()
            {
                    if( m_in == NULL)
                        m_in = new WMInput();
                return m_in;
            }

            WMOutput*  WMInstance::getOutput()
            {
                    if( m_out == NULL)
                        m_out = new WMOutput();
                return m_out;
            }

            WMManager* WMInstance::getManager()
            {
                    if( m_mgr == NULL)
                        m_mgr = new WMManager();
                return m_mgr;
            }

            Atom  WMInstance::getAtom(std::string atomName)
            {
                return XInternAtom(m_dsp, atomName.c_str(), 0);
            }

            void  WMInstance::end()
            {
                if( m_mgr != NULL)
                {
                    m_mgr->Terminate();
                    delete m_mgr;
                }

                delete m_in;
                delete m_out;
            }
