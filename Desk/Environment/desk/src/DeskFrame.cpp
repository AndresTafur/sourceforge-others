
#include "config.h"
#include "rcids.h"
#include "Background.h"
#include "DeskFrame.h"


#ifdef _WITH_PLAYER_
#include "player/MusicLabel.h"
#endif



DeskFrame::DeskFrame(wxString str) : wxFrame(NULL,ID_FRM, wxT("Desktop"), wxPoint(0,0), wxSize(1024,768),wxFRAME_NO_TASKBAR|wxBORDER_NONE, wxT("Desk"))
{
  wxBitmap image(str + wxT("/data/pix/bg.jpg"),wxBITMAP_TYPE_ANY);
  wxBitmap image2(str + wxT("/data/pix/computer.png"),wxBITMAP_TYPE_ANY);
  wxGridSizer *sizer = new wxGridSizer(1,1);
      
      bmp = new Background(this,image);
      pc  = new Icon(this,image2);
     
	sizer->Add(pc,1);

	SetSizer(sizer);

#ifdef _WITH_PLAYER_
      MusicLabel *button = new MusicLabel(this,str,wxSize(1024,768));
#endif	
}

