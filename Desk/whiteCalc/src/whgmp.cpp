#include <gmp.h>

class whiteNum : public mpf_class
{
public

	whiteNum(wxString str) : mpf_class( str.ToAscii() )
	{

	}

	

	wxString  getwxString()
	{


	}


};
