#ifndef _WMLISTENER_
#define _WMLISTENER_

#include "WMEvent.hh"

class WMListener
{
public:

        virtual void onEvent(WMEvent evt) = 0;
};

#endif
