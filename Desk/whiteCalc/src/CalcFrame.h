#include "CalcInterpreter.cpp"

enum buttons {
    ID_0 = 0, ID_1, ID_2,
    ID_3    , ID_4, ID_5,
    ID_6    , ID_7, ID_8,
    ID_9,
    ID_DOT  , ID_EQU,
    ID_ADD  , ID_SUS, ID_MULT, ID_DIV,
    ID_CLS  , ID_BCK,
    ID_PO   , ID_PC, ID_PERCENT, ID_RECIPROCAL, ID_CHANGESIGN,
    ID_SQUARE,ID_SQUAREROOT,
    ID_BASICA,ID_AVANZADA,ID_CIENTIFICA
};

enum modes {
    BASIC = 0,
    ADVANCED = 1
};

class CalcFrame : public wxFrame
{
public:
    CalcFrame(modes type);
    ~CalcFrame();

    void onNumberAdded(wxCommandEvent &e);
    void onReciprocalAdded(wxCommandEvent &e);
    void onSignChanged(wxCommandEvent &e);
    void KeyPressed(wxKeyEvent &event);
    void GetResult(wxCommandEvent &e);

    void CreateBasicCalculator(wxCommandEvent &e);
    void CreateAdvancedCalculator(wxCommandEvent &e);
    void ProcessResult();
    void Clear();
    void Back();
    void ChangeSign();

    void Quit(wxCommandEvent &evt);
    void About(wxCommandEvent &evt);

private:
    wxTextCtrl  *display;
    wxButton *btn_calc;
    wxGridSizer *grid;
    wxBoxSizer  *sizer;
    modes   _tipo;
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

EVT_BUTTON(ID_PO,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_PC,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_PERCENT,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_RECIPROCAL,CalcFrame::onReciprocalAdded)
EVT_BUTTON(ID_CHANGESIGN,CalcFrame::onSignChanged)
EVT_BUTTON(ID_SQUAREROOT,CalcFrame::onNumberAdded)
EVT_BUTTON(ID_SQUARE,CalcFrame::onNumberAdded)

EVT_BUTTON(ID_EQU,CalcFrame::GetResult)

EVT_KEY_UP(CalcFrame::KeyPressed)


EVT_MENU(ID_BASICA,CalcFrame::CreateBasicCalculator)
EVT_MENU(ID_AVANZADA,CalcFrame::CreateAdvancedCalculator)

END_EVENT_TABLE()

