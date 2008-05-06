#include <wx/wx.h>
#include <wx/animate.h>

#include "WhiteHawkThread.h"
#include "Frame.cpp"


class Splash : public wxApp
{
public:    
            bool OnInit()
            {
               wxString str;
              ::wxInitAllImageHandlers();

	    	str << this->argv[0];
	    	str = str.BeforeLast( '/'); 
              
              Frame *frame = new Frame(str);
              
	      SetTopWindow(frame);
              frame->Show();  
	      frame->WhiteHawkThread::Create();
              return true;  
            }
    
    
    
    
};

IMPLEMENT_APP(Splash)
