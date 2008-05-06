
#ifndef _WX_CIRCLE_TOGGLE_BUTTON_
#define _WX_CIRCLE_TOGGLE_BUTTON_
#include "wxCircleButton.hh"

class wxCircleToggleButton : public wxCircleButton
{
public:

    wxCircleToggleButton(wxWindow* parent,wxWindowID id, wxBitmap bmp,wxBitmap bmph);

	bool GetValue();

	void SetValue(const bool state);

	void OnPress(wxMouseEvent &evt);




protected:
const static int ID_PRESSED = 100;
const static int ID_NORMAL  = 101;
int stat;
int x,y;

DECLARE_EVENT_TABLE()

};
#endif
