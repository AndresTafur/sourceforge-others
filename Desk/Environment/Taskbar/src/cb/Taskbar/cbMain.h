/***************************************************************
 * Name:      cbMain.h
 * Purpose:   Defines Application Frame
 * Author:    Jorge Andres Tafur (darkhawk665@yahoo.com)
 * Created:   2007-12-02
 * Copyright: Jorge Andres Tafur (whitehawk.servehttp.com)
 * License:
 **************************************************************/

#ifndef CBMAIN_H
#define CBMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "cbApp.h"

class cbFrame: public wxFrame
{
    public:
        cbFrame(wxFrame *frame, const wxString& title);
        ~cbFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // CBMAIN_H
