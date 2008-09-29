/*  This file is part of WhiteHawkClamav.

    WhiteHawkClamav is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WhiteHawkClamav is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with WhiteHawkClamav.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <wx/wx.h>
#include <wx/animate.h>
#include <wx/splash.h>
#include <X11/Xlib.h>

#include "GUI/AvFrame.hh"
#include "ClamLayer/ClamavInstance.hh"

class MyApp: public wxApp
{

   bool OnInit()
    {
     wxString str = DATA_DIR"/splash.png";
     wxBitmap bitmap(str);
     AvFrame *frame = NULL;
     wxSplashScreen* splash;

      ::wxInitAllImageHandlers();


      splash = new wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN,5, NULL, -1,wxDefaultPosition,wxDefaultSize,0);
      splash->Show(TRUE);
      splash->Update();
      wxYield();


      str << this->argv[0];

      str   = str.BeforeLast( '/');
      frame = new AvFrame( str);

      WhiteHawkClamav::ClamavInstance::getInstance()->loadDatabase();
      frame->Show(TRUE);
      this->SetTopWindow(frame);

      if( splash)
        splash->Destroy();


     return TRUE;
   }

};

IMPLEMENT_APP_NO_MAIN(MyApp)




int main(int argc, char *argv[])
{
   int ret_val;

	XInitThreads();
	ret_val = wxEntry(argc, argv);

    WhiteHawkClamav::ClamavInstance::getInstance()->destroy();

	return ret_val;
}
