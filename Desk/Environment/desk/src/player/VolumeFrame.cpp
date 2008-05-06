#include "VolumeFrame.h"
#include "../rcids.h"


VolumeFrame::VolumeFrame(wxWindow *parent, OutputStreamPtr sound) : wxDialog(parent, wxID_ANY, wxT(""))
{  

 this->sound = sound;
  vol = new wxSlider(this, ID_VOLCTRL, 100 , 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_INVERSE|wxSL_LABELS);

  vol->SetValue(100);
  wxSize size = vol->GetSize();

    size.SetHeight( size.GetHeight()+100  );
    size.SetWidth( 50);

  this->Centre();
  this->SetClientSize(size);

}



void VolumeFrame::onChange(wxScrollEvent &e)
{
	  sound->setVolume( ((float)vol->GetValue())/100 );
}







BEGIN_EVENT_TABLE(VolumeFrame,wxDialog)
EVT_SCROLL_THUMBTRACK(VolumeFrame::onChange)
END_EVENT_TABLE()
