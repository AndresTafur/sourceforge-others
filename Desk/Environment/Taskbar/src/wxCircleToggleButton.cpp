#include "wxCircleToggleButton.hh"



wxCircleToggleButton::wxCircleToggleButton(wxWindow* parent,wxWindowID id, wxBitmap bmp,wxBitmap bmph) : wxCircleButton(parent,id,bmp,bmph)
	{
		stat = ID_NORMAL;
	}


	bool wxCircleToggleButton::GetValue()
	{
	  return (stat-100);
	}

	void wxCircleToggleButton::SetValue(const bool state)
	{
		if( state )
		{
			Draw(hover);
			stat = ID_PRESSED;
		}
		else
		{
			Draw(normal);
			x = y = 0;
			stat = ID_NORMAL;
		}
	}

	void wxCircleToggleButton::OnPress(wxMouseEvent &evt)
	{

		if( stat == ID_NORMAL)
		   SetValue(true);
		else
		   SetValue(false);

		wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, this->GetId());
		event.SetEventObject( this );

 		parent->GetEventHandler()->ProcessEvent(event);

 	}





BEGIN_EVENT_TABLE(wxCircleToggleButton,wxControl)
	EVT_LEFT_DOWN(wxCircleToggleButton::OnPress)
	EVT_LEFT_DCLICK(wxCircleToggleButton::OnPress)
	EVT_ENTER_WINDOW(wxCircleToggleButton::OnFocus)
	EVT_LEAVE_WINDOW(wxCircleToggleButton::OnLost)
	EVT_PAINT(wxCircleToggleButton::OnPaint)
END_EVENT_TABLE()
