
#include <audiere.h>
#include <wx/wx.h>
#include <wx/slider.h>


using namespace audiere;

class VolumeFrame : public wxDialog
{
public:

	VolumeFrame(wxWindow *parent, OutputStreamPtr sound);

	void onChange(wxScrollEvent &e);

protected:
wxSlider *vol;
OutputStreamPtr sound;
DECLARE_EVENT_TABLE()

};
