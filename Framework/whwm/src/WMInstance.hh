#ifndef _XLIB_INSTANCE_
#define _XLIB_INSTANCE_

#include <X11/Xlib.h>

#include "WMInput.hh"
#include "WMOutput.hh"
#include "WMManager.hh"


class WMInstance
{
protected:
           WMInstance();

public:
           static  void init();

           static  Display*   getDisplay();

           static  Window     getRoot();

           static  WMInput*   getInput();

           static  WMOutput*  getOutput();

           static  WMManager* getManager();

           static  Atom       getAtom(std::string atomName);

           static  void end();


protected:
static Display   *m_dsp;
static Window     m_root;
static WMInput   *m_in;
static WMOutput  *m_out;
static WMManager *m_mgr;
};

#endif
