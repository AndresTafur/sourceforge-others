/*  This file is part of WhiteHawkClamav,
 *  Copyright (C) 2007 - 2008 Jorge Tafur <darkhawk665@users.sf.net>.
 *
 *   WhiteHawkClamav is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   WhiteHawkClamav is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with WhiteHawkClamav.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <wx/wx.h>
#include <wx/animate.h>
#include <wx/splash.h>
#include <X11/Xlib.h>

#include <Exception.hh>

#include "config.h"

#include "GUI/AvFrame.hh"
#include "GUI/TrayIcon.hh"

#undef wxT
#define wxT(data) wxString::FromAscii(data)


class MyApp: public wxApp
{

   bool OnInit()
    {
     wxString str = wxT(DATA_DIR"/splash.png");
     wxBitmap bitmap(str);
     wxSplashScreen *splash;
     wxIcon appIcon;

      ::wxInitAllImageHandlers();


      splash = new wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN,5, NULL, -1,wxDefaultPosition,wxDefaultSize,0);
      splash->Show(TRUE);
      splash->Update();
      wxYield();


      str << this->argv[0];

      str   = str.BeforeLast( '/');
      appIcon.LoadFile(wxT(DATA_DIR"/whclicon.png"), wxBITMAP_TYPE_ANY);
      m_frame = new AvFrame(str,appIcon);

      WhiteHawkClamav::ClamavInstance::getInstance()->loadDatabase();

      m_frame->Show(TRUE);
      this->SetTopWindow(m_frame);


      if( splash)
        splash->Destroy();

      m_frame->createTrayIcon();

     return TRUE;
   }

private:
AvFrame *m_frame;


};

IMPLEMENT_APP_NO_MAIN(MyApp)




int main(int argc, char *argv[])
{
   int ret_val;


        setlocale (LC_CTYPE, "");
        setlocale (LC_MESSAGES, "");

        bindtextdomain (PACKAGE, LOCALEDIR);
        textdomain (PACKAGE);

        XInitThreads();
        ret_val = wxEntry(argc, argv);

        wxEntryCleanup();

        WhiteHawkClamav::ClamavInstance::destroy();

	return ret_val;
}
