
#ifndef _CLIENT_LIST_ITEM_
#define _CLIENT_LIST_ITEM_

#include "ClientButton.hh"




class ClientListItem : public ClientButton
{
public:

	ClientListItem(wxWindow* parent,wxWindowID id, Window window, wxString label, SystemUtils *sysUtils);



protected:
ClientListItem *befo;
ClientListItem *next;
int index;
};

#endif
