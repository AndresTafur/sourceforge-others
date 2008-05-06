/***************************************************************
 * Name:      cbApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Jorge Andres Tafur (darkhawk665@yahoo.com)
 * Created:   2007-12-02
 * Copyright: Jorge Andres Tafur (whitehawk.servehttp.com)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "cbApp.h"
#include "cbMain.h"

IMPLEMENT_APP(cbApp);

bool cbApp::OnInit()
{
    cbFrame* frame = new cbFrame(0L, _("wxWidgets Application Template"));
    
    frame->Show();
    
    return true;
}
