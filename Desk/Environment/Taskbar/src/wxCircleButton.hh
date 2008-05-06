
#ifndef _WX_CIRCLE_BUTTON_
#define _WX_CIRCLE_BUTTON_
#include <wx/wx.h>
#include <wx/control.h>



class wxCircleButton : public wxControl
{
public:

    wxCircleButton(wxWindow* parent,wxWindowID id,wxBitmap bmp,wxBitmap bmph);

	void Draw(wxBitmap bmp);

	void OnPaint(wxPaintEvent &event);

	void OnPress(wxMouseEvent &evt);


	void OnRelease(wxMouseEvent &evt);


	void OnFocus(wxMouseEvent &evt);


	void OnLost(wxMouseEvent &evt);


protected:
wxBitmap normal;
wxBitmap hover;

wxPaintDC *dc;
wxWindow *parent;
DECLARE_EVENT_TABLE()

};
#endif
