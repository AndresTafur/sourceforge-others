#include "MusicLabel.h"
#include "../rcids.h"
#include "VolumeFrame.h"

MusicLabel::MusicLabel(wxWindow *parent, wxString str, wxSize size): wxBitmapButton(parent,wxID_ANY,wxNullBitmap,wxPoint(760,10),wxDefaultSize)
 {
	
     this->SetBitmapLabel( str + "/data/pix/stop.png");	
     menu  = new wxMenu;
     menu2 = new wxMenu;


     menu->Append(wxID_OPEN, wxT("&Abrir"),wxT(""), wxITEM_NORMAL);
     menu->Append(ID_VOL, wxT("&Volumen"),wxT(""), wxITEM_NORMAL);
     menu->Append(ID_REPEAT, wxT("R&epetir"),wxT("") , wxITEM_CHECK);
     menu->AppendSeparator();
     menu->Append(ID_PLAY, wxT("&Reproducir")   ,wxT("")  , wxITEM_NORMAL);
     menu->Append(ID_PAUSE, wxT("&Pausar")   ,wxT("")  , wxITEM_NORMAL);
     menu->Append(ID_STOP, wxT("&Detener")   ,wxT("")  , wxITEM_NORMAL);

	  this->SetForegroundColour(wxColour("WHITE"));
	  this->SetBackgroundColour(wxColour("CORNFLOWER BLUE"));

    this->str = str;
 }


 void MusicLabel::ThreadRoutine()
 {
	openMusic();
 }


 bool MusicLabel::openFileDlg()
 {
   wxFileDialog *dlg = new wxFileDialog(this, wxT("Choose a file"),wxT(""),wxT("music.mp3"),wxT("*.*"));

		if( dlg->ShowModal() == wxID_OK)
		{
		    path = dlg->GetPath();
		    return true;
		}
   return false;
 }


void MusicLabel::openMusic()
{
	if( !device)
	  device = OpenDevice("");

	if( device )
	{
	  sound = OpenSound(device, path.c_str());

	  if( sound )		     
	   sound->play();
	}

}


void MusicLabel::play()
{
   sound->play();
}

void MusicLabel::pause()
{
   sound->stop();   
}

void MusicLabel::stop()
{
   sound->stop();   	
   sound->reset();
}


 void MusicLabel::onAction(wxCommandEvent &evt)
 {
   
	switch( evt.GetId() )
	{
	  case wxID_OPEN:
		  if( openFileDlg() )
		  {
			WhiteHawkThread::Create();
		        this->SetToolTip(path.AfterLast('/'));
		  }
		break;

	  case ID_PLAY:
                if(sound)
		  play();
		break;


	  case ID_VOL:
		if( sound )
		(VolumeFrame(this,sound)).ShowModal();
	       break;

	  case ID_PAUSE:
	      if( sound)
	       	pause();
	       break;

	  case ID_STOP:
 	     if(sound)
		 stop();
	       break;

	}


 }


 void MusicLabel::OnClick(wxMouseEvent &evt)
 {
	if( sound)
	{
	  if(!sound->isPlaying())	
		play();
	  else
		pause();
	}

 }


 void MusicLabel::OnRightClick(wxMouseEvent &evt)
 {
	PopupMenu(menu);
 }


BEGIN_EVENT_TABLE(MusicLabel,wxBitmapButton)
EVT_LEFT_DOWN(MusicLabel::OnClick)
EVT_RIGHT_DOWN(MusicLabel::OnRightClick)
EVT_MENU(wxID_OPEN,MusicLabel::onAction)
EVT_MENU(ID_VOL,MusicLabel::onAction)
EVT_MENU(ID_PLAY,MusicLabel::onAction)
EVT_MENU(ID_PAUSE,MusicLabel::onAction)
EVT_MENU(ID_STOP,MusicLabel::onAction)
END_EVENT_TABLE()

