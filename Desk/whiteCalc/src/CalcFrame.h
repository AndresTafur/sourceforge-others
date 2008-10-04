#include "CalcInterpreter.cpp"

enum buttons {
    ID_0 = 0, ID_1, ID_2,
    ID_3    , ID_4, ID_5,
    ID_6    , ID_7, ID_8,
    ID_9,
    ID_DOT  , ID_EQU,
    ID_ADD  , ID_SUS, ID_MULT, ID_DIV,
    ID_CLS  , ID_BCK
};

class CalcFrame : public wxFrame
{
public:
    CalcFrame();

    void onNumberAdded(wxCommandEvent &e);
    void GetResult(wxCommandEvent &e);

    void Quit(wxCommandEvent &evt);
    void About(wxCommandEvent &evt);

private:
    wxTextCtrl  *display;
    DECLARE_EVENT_TABLE();
};


BEGIN_EVENT_TABLE(CalcFrame,wxFrame)

EVT_MENU(wxID_EXIT, CalcFrame::Quit)
EVT_MENU(wxID_ABOUT, CalcFrame::About)

EVT_BUTTON(ID_0,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_1,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_2,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_3,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_4,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_5,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_6,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_7,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_8,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_9,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_DOT,CalcFrame::onNumberAdded)

EVT_BUTTON(ID_ADD,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_SUS,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_DIV,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_MULT,CalcFrame::onNumberAdded)

EVT_BUTTON(ID_EQU,CalcFrame::GetResult)

END_EVENT_TABLE()
