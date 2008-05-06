
#include "wxCircleButton.hh"

wxCircleButton::wxCircleButton(wxWindow* parent,wxWindowID id,wxBitmap bmp,wxBitmap bmph) : wxControl(parent,id)
	{
		this->parent = parent;
		this->SetBackgroundColour( parent->GetBackgroundColour());
		this->SetForegroundColour( parent->GetForegroundColour());

		normal = bmp;
		hover  = bmph;

		this->SetSize(normal.GetWidth()+1,normal.GetHeight()+1);
	}

	void wxCircleButton::Draw(wxBitmap bmp)
	{
		dc->DrawBitmap(bmp,0, 0, true);
	}

	void wxCircleButton::OnPaint(wxPaintEvent &event)
	{
		 dc = new wxPaintDC(this);
		 Draw(normal);
	}

	void wxCircleButton::OnPress(wxMouseEvent &evt)
	{
			wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, this->GetId());
			event.SetEventObject( this );

			Draw(hover);
 			parent->GetEventHandler()->ProcessEvent(event);
 	}


	void wxCircleButton::OnRelease(wxMouseEvent &evt)
	{
			dc->ResetBoundingBox();
			Draw(hover);
	}


	void wxCircleButton::OnFocus(wxMouseEvent &evt)
	{
			Draw(hover);
	}


	void wxCircleButton::OnLost(wxMouseEvent &evt)
	{
		  Draw(normal);
	}


BEGIN_EVENT_TABLE(wxCircleButton,wxControl)
	EVT_LEFT_DOWN(wxCircleButton::OnPress)
	EVT_LEFT_DCLICK(wxCircleButton::OnPress)
	EVT_LEFT_UP(wxCircleButton::OnRelease)
	EVT_ENTER_WINDOW(wxCircleButton::OnFocus)
	EVT_LEAVE_WINDOW(wxCircleButton::OnLost)
	EVT_PAINT(wxCircleButton::OnPaint)
END_EVENT_TABLE()
