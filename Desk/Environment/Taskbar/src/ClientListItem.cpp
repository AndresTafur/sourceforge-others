#include "ClientListItem.hh"


	ClientListItem::ClientListItem(wxWindow* parent,wxWindowID id, Window window, wxString label, SystemUtils *sysUtils) :
			      ClientButton(parent, id, window, label, sysUtils)
	{
		befo  = NULL;
		next  = NULL;
		index = 0;
	}


