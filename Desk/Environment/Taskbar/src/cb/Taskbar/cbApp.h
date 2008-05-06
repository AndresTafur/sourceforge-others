/***************************************************************
 * Name:      cbApp.h
 * Purpose:   Defines Application Class
 * Author:    Jorge Andres Tafur (darkhawk665@yahoo.com)
 * Created:   2007-12-02
 * Copyright: Jorge Andres Tafur (whitehawk.servehttp.com)
 * License:
 **************************************************************/

#ifndef CBAPP_H
#define CBAPP_H

#include <wx/app.h>

class cbApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // CBAPP_H
