#include "CalcFrame.h"

CalcFrame::~CalcFrame()
{
    /*delete(display);
    delete(btn_calc);
    delete(grid);
    delete(sizer);*/
}

CalcFrame::CalcFrame(modes tipo) : wxFrame(NULL,wxID_ANY, wxT("WhiteHawkCalculator"), wxDefaultPosition, wxDefaultSize,  wxCAPTION | wxMINIMIZE_BOX | wxCLOSE_BOX | wxRESIZE_BORDER , wxT("WhiteCalc"))
{
    wxMenuBar   *bar    = new wxMenuBar;

    wxMenu      *calc   = new wxMenu;
    wxMenu      *edit   = new wxMenu;
    wxMenu      *view   = new wxMenu;
    wxMenu      *help   = new wxMenu;

    sizer  = new wxBoxSizer(wxVERTICAL);

    bar->Append(calc, wxT("&Calculadora"));
        bar->Append(edit, wxT("&Editar"));
        bar->Append(view, wxT("&Ver"));
        bar->Append(help, wxT("&Ayuda"));


    calc->Append(wxID_SAVE,wxT("&Guardar"), wxT("Guarda el dato actual"));
    calc->Append(wxID_SAVEAS,wxT("Guardar &como"), wxT("Guarda en un nuevo documento"));
    calc->AppendSeparator();
    calc->Append(wxID_EXIT,wxT("&Salir"), wxT("Sale de este programa"));

    edit->Append(wxID_CUT,wxT("Cor&tar"), wxT("Corta la seleccion"));
    edit->Append(wxID_COPY,wxT("&Copiar"),wxT("Copia la seleccion"));
    edit->Append(wxID_PASTE,wxT("&Pegar"),wxT("Pega  la seleccion"));

    view->Append(0,wxT("&Basica"));
    view->Append(0,wxT("&Avanzada"));
    view->Append(0,wxT("&Cientifica"));
    help->Append(wxID_HELP,wxT("&Ayuda"),wxT("Ayuda de este programa"));
    help->Append(wxID_ABOUT,wxT("A&cerca de"), wxT("Acerca de este programa"));

    display = new wxTextCtrl(this, -1, wxT(""), wxPoint(-1, -1),
    wxSize(-1, -1), wxTE_RIGHT+wxTE_READONLY);

    sizer->Add(display, 0, wxEXPAND | wxTOP | wxBOTTOM, 4);

    _tipo=tipo;
    switch(_tipo)
    {
        case BASIC:
            grid = new wxGridSizer(5,4,5,5);
            grid->Add(new wxButton(this, ID_CLS, wxT("&Cls")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_BCK, wxT("Bck")), 0, wxEXPAND);
            grid->Add(new wxStaticText(this, -1, wxT("")), 0, wxEXPAND);
            grid->Add(new wxStaticText(this, -1, wxT("")), 0, wxEXPAND);

            grid->Add(new wxButton(this, ID_7, wxT("7")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_8, wxT("8")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_9, wxT("9")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_DIV, wxT("/")), 0, wxEXPAND);

            grid->Add(new wxButton(this, ID_4, wxT("4")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_5, wxT("5")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_6, wxT("6")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_MULT, wxT("*")), 0, wxEXPAND);

            grid->Add(new wxButton(this, ID_1, wxT("1")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_2, wxT("2")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_3, wxT("3")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_SUS, wxT("-")), 0, wxEXPAND);

            grid->Add(new wxButton(this, ID_0, wxT("0")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_DOT, wxT(".")), 0, wxEXPAND);
            btn_calc= new wxButton(this, ID_EQU, wxT("="));
            grid->Add(btn_calc, 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_ADD, wxT("+")), 0, wxEXPAND);
            break;
        case ADVANCED:
            grid = new wxGridSizer(5,4,5,5);
            grid->Add(new wxButton(this, ID_CLS, wxT("Cls")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_BCK, wxT("Bck")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_PO, wxT("(")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_PC, wxT(")")), 0, wxEXPAND);

            grid->Add(new wxButton(this, ID_7, wxT("7")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_8, wxT("8")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_9, wxT("9")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_DIV, wxT("/")), 0, wxEXPAND);

            grid->Add(new wxButton(this, ID_4, wxT("4")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_5, wxT("5")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_6, wxT("6")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_MULT, wxT("*")), 0, wxEXPAND);

            grid->Add(new wxButton(this, ID_1, wxT("1")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_2, wxT("2")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_3, wxT("3")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_SUS, wxT("-")), 0, wxEXPAND);

            grid->Add(new wxButton(this, ID_0, wxT("0")), 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_DOT, wxT(".")), 0, wxEXPAND);
            btn_calc= new wxButton(this, ID_EQU, wxT("="));
            grid->Add(btn_calc, 0, wxEXPAND);
            grid->Add(new wxButton(this, ID_ADD, wxT("+")), 0, wxEXPAND);
            break;
    }


    this->SetMenuBar(bar);
    this->CreateStatusBar();
    this->Layout();
    sizer->Add(grid, 1, wxEXPAND);
    this->SetSizer(sizer);
    this->SetMinSize(wxSize(150, 150));
    this->Centre();
    Clear();
    btn_calc->SetFocus();
}

void CalcFrame::CreateBasicCalculator()
{
    CalcFrame* frame = new CalcFrame(BASIC);
    frame->Show();
    this->Destroy();
}

void CalcFrame::CreateAdvancedCalculator()
{
    CalcFrame* frame = new CalcFrame(ADVANCED);
    frame->Show();
    this->Destroy();
}

void CalcFrame::KeyPressed(wxKeyEvent &event)
{
    char key=event.GetRawKeyCode();

    if(display->GetValue().Cmp(wxT("0")) == 0)
        display->SetValue(wxT(""));

    wxString str = wxString::FromAscii(key);
    switch(_tipo)
    {
        case BASIC:
            switch(key)
            {
                case 48:
                case WXK_NUMPAD0:
                    str = wxT("0");
                    break;
                case 49:
                case WXK_NUMPAD1:
                    str = wxT("1");
                    break;
                case 50:
                case WXK_NUMPAD2:
                    str = wxT("2");
                    break;
                case 51:
                case WXK_NUMPAD3:
                    str = wxT("3");
                    break;
                case 52:
                case WXK_NUMPAD4:
                    str = wxT("4");
                    break;
                case 53:
                case WXK_NUMPAD5:
                    str = wxT("5");
                    break;
                case 54:
                case WXK_NUMPAD6:
                    str = wxT("6");
                    break;
                case 55:
                case WXK_NUMPAD7:
                    str = wxT("7");
                    break;
                case 56:
                case WXK_NUMPAD8:
                    str = wxT("8");
                    break;
                case 57:
                case WXK_NUMPAD9:
                    str = wxT("9");
                    break;
                case WXK_NUMPAD_ADD:
                    str = wxT("+");
                    break;
                case WXK_NUMPAD_SUBTRACT:
                    str = wxT("-");
                    break;
                case WXK_NUMPAD_DIVIDE:
                    str = wxT("/");
                    break;
                case WXK_NUMPAD_MULTIPLY:
                    str = wxT("*");
                    break;
                case WXK_NUMPAD_DECIMAL:
                    str = wxT(".");
                    break;
                case WXK_ESCAPE:
                    str = wxT("");
                    Clear();
                    break;
                case WXK_RETURN:
                case WXK_NUMPAD_ENTER:
                    str = wxT("");
                    ProcessResult();
                    break;
                case WXK_BACK:
                    str = wxT("");
                    Back();
                    break;
                default:
                    str = wxT("");
                    break;
            }
            break;
        case ADVANCED:
            switch(key)
            {
                case 48:
                case WXK_NUMPAD0:
                    str = wxT("0");
                    break;
                case 49:
                case WXK_NUMPAD1:
                    str = wxT("1");
                    break;
                case 50:
                case WXK_NUMPAD2:
                    str = wxT("2");
                    break;
                case 51:
                case WXK_NUMPAD3:
                    str = wxT("3");
                    break;
                case 52:
                case WXK_NUMPAD4:
                    str = wxT("4");
                    break;
                case 53:
                case WXK_NUMPAD5:
                    str = wxT("5");
                    break;
                case 54:
                case WXK_NUMPAD6:
                    str = wxT("6");
                    break;
                case 55:
                case WXK_NUMPAD7:
                    str = wxT("7");
                    break;
                case 56:
                case WXK_NUMPAD8:
                    str = wxT("8");
                    break;
                case 57:
                case WXK_NUMPAD9:
                    str = wxT("9");
                    break;
                case WXK_NUMPAD_ADD:
                    str = wxT("+");
                    break;
                case WXK_NUMPAD_SUBTRACT:
                    str = wxT("-");
                    break;
                case WXK_NUMPAD_DIVIDE:
                    str = wxT("/");
                    break;
                case WXK_NUMPAD_MULTIPLY:
                    str = wxT("*");
                    break;
                case WXK_NUMPAD_DECIMAL:
                    str = wxT(".");
                    break;
                case 40:
                    str = wxT("(");
                    break;
                case 41:
                    str = wxT(")");
                    break;
                case WXK_ESCAPE:
                    str = wxT("");
                    Clear();
                    break;
                case WXK_RETURN:
                case WXK_NUMPAD_ENTER:
                    str = wxT("");
                    ProcessResult();
                    break;
                case WXK_BACK:
                    str = wxT("");
                    Back();
                    break;
                default:
                    str = wxT("");
                    break;
            }
            break;
    }

    display->AppendText(str);
    btn_calc->SetFocus();
}

void CalcFrame::onNumberAdded(wxCommandEvent &e)
{
    wxString str = ((wxButton*)e.GetEventObject())->GetLabel();
    if(display->GetValue().Cmp(wxT("0")) == 0)
        display->SetValue(wxT(""));

    display->AppendText(str);
}

void CalcFrame::GetResult(wxCommandEvent &e)
{
    ProcessResult();
}

void CalcFrame::Clear()
{
    display->SetValue(wxT("0"));
}

void CalcFrame::Back()
{
    display->SetValue(display->GetValue().RemoveLast());
    if(display->GetValue()==wxT(""))
    {
        display->SetValue(wxT("0"));
    }
    CreateAdvancedCalculator();
}

void CalcFrame::ProcessResult()
{
    wxString result = display->GetValue();
    CalcEngine *ce = new CalcEngine();
    result = ce->Process(result);
    delete ce;
    display->SetValue(result);
}

void CalcFrame::Quit(wxCommandEvent &evt)
{
    exit(0);
}

void CalcFrame::About(wxCommandEvent &evt)
{
    wxMessageBox(_T("Esta es la calculadora de whiteHawk\n\nDesarrollada por Juan Cruz Martinez (c) 2008"),wxT("Acerca de..."), wxOK| wxICON_INFORMATION,this);
}
