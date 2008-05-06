
#include "Background.h"
#include "Icon.h"

#ifndef _DESK_FRAME_
#define _DESK_FRAME_

class DeskFrame : public  wxFrame
{
public:

	DeskFrame(wxString str);


protected:
Background *bmp;
Icon	*pc;

};
#endif




