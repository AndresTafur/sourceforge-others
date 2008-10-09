#include <wx/wx.h>

#include "CalcFrame.cpp"

class WhiteCalc: public wxApp
{
    bool OnInit()
    {
        ::wxInitAllImageHandlers();
        CalcFrame *frame = new CalcFrame(BASIC);

        frame->Show(true);
        this->SetTopWindow(frame);
        return TRUE;
    }
};



IMPLEMENT_APP(WhiteCalc)
