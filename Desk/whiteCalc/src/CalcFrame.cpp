#include "CalcInterpreter.cpp"



enum
{
    ID_1 = 0, ID_2, ID_3,
    ID_4,     ID_5, ID_6,
    ID_7,     ID_8, ID_9,
    ID_0,   ID_SCR, ID_ADD,
    ID_SUS, ID_MUL, ID_DIV,
    ID_DOT, ID_EDIT,ID_VIEW,
    ID_HELP,ID_EQU,
};


class CalcFrame : public  wxFrame
{
public:

        CalcFrame() : wxFrame(NULL,wxID_ANY, wxT("WhiteHawkCalculator"), wxDefaultPosition, wxDefaultSize,  wxCAPTION | wxMINIMIZE_BOX | wxCLOSE_BOX | wxRESIZE_BORDER , wxT("WhiteCalc"))
        {
            wxMenuBar   *bar    = new wxMenuBar;

	    wxMenu      *calc   = new wxMenu;
            wxMenu      *edit   = new wxMenu;
            wxMenu      *view   = new wxMenu;
            wxMenu      *help   = new wxMenu;

            wxBoxSizer  *sizer  = new wxBoxSizer(wxVERTICAL);
            wxGridSizer *grid   = new wxGridSizer(5,4,5,5);



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


            wxButton    *add    = new wxButton(this,ID_ADD,wxT("+"),wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,wxT("bot"));
            wxButton    *sus    = new wxButton(this,ID_SUS,wxT("-"),wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,wxT("bot"));
            wxButton    *mul    = new wxButton(this,ID_MUL,wxT("x"),wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,wxT("bot"));
            wxButton    *div    = new wxButton(this,ID_DIV,wxT("/"),wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,wxT("bot"));
                         dot    = new wxButton(this,ID_DOT,wxT("."),wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,wxT("bot"));
            wxButton    *equ    = new wxButton(this,ID_EQU,wxT("="),wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,wxT("bot"));

            wxString    tmp;
            wxButton    *numbers[10];


                scr  = new wxTextCtrl(this,ID_SCR, wxT("0"),wxDefaultPosition, wxDefaultSize,wxTE_RIGHT, wxDefaultValidator,wxT("edit"));
                oper = new CalcInterpreter;


                for( int i=0; i < 10; i++)
                {
                        tmp.Printf(wxT("%i"),i);
                        numbers[i] = new wxButton(this,i,tmp,wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,wxT("bot"));
                }

                for( int i=7; i < 10; i++)
                    grid->Add(numbers[i]);
                grid->Add(div);


                for( int i=4; i < 7; i++)
                    grid->Add(numbers[i]);
                grid->Add(mul);

                for( int i=1; i < 4; i++)
                    grid->Add(numbers[i]);
                grid->Add(sus);


                grid->Add(numbers[0]);
                grid->Add(dot);
                grid->Add(equ);
                grid->Add(add);


                scr->SetEditable(false);

                sizer->Add(scr,0,wxEXPAND,20,0);
                sizer->AddSpacer(20);
                sizer->Add(grid,0,wxEXPAND,20,0);

		this->Centre();
                this->SetSizer(sizer);
                this->SetMenuBar(bar);
                this->CreateStatusBar();
                this->Layout();

        }


        void validateDec()
        {
            if( scr->GetValue().Contains(wxT(",")))
                dot->Enable(false);
            else
                dot->Enable(true);
        }


        void onNumber(wxCommandEvent &e)
        {
            wxString str = ((wxButton*)e.GetEventObject())->GetLabel();


                if( scr->GetValue().Cmp(wxT("0")) == 0 || clear)
                        scr->SetValue(wxT(""));

                scr->AppendText( str );
                this->validateDec();
                clear = false;
        }

        void onAction(wxCommandEvent &e)
        {

            switch( e.GetId() )
            {
                    case ID_ADD:
                        oper->setNum1( scr->GetValue() );
                        oper->setOper( CalcInterpreter::ID_SUM );
                        clear = true;
                        break;

                    case ID_SUS:
                        oper->setNum1( scr->GetValue() );
                        oper->setOper( CalcInterpreter::ID_SUS );
                        clear = true;
                        break;

                    case ID_MUL:
                        oper->setNum1( scr->GetValue() );
                        oper->setOper( CalcInterpreter::ID_MUL );
                        clear = true;
                        break;

                    case ID_DIV:
                        oper->setNum1( scr->GetValue() );
                        oper->setOper( CalcInterpreter::ID_DIV );
                        clear = true;
                        break;

                    case ID_EQU:
                        oper->setNum2( scr->GetValue() );
                        scr->SetValue( oper->operate());
                        this->validateDec();
                        clear = true;
                        break;

                    case ID_DOT:
                            scr->AppendText(wxT(","));
                            this->validateDec();
                            clear = false;
                        break;

            }

        }


	void Quit(wxCommandEvent &evt)
	{
		exit(0);
	}


	void About(wxCommandEvent &evt)
	{
	  wxMessageBox(_T("Esta es la calculadora de whiteHawk\n\nDesarrollada por Jorge Andres Tafur (c) 2007"),wxT("Acerca de..."), wxOK| wxICON_INFORMATION,this);
	}

private:
wxTextCtrl  *scr;
wxButton    *dot;
bool        clear;
CalcInterpreter *oper;
DECLARE_EVENT_TABLE();

};

BEGIN_EVENT_TABLE(CalcFrame,wxFrame)
EVT_BUTTON(ID_0,CalcFrame::onNumber)
EVT_BUTTON(ID_1,CalcFrame::onNumber)
EVT_BUTTON(ID_2,CalcFrame::onNumber)
EVT_BUTTON(ID_3,CalcFrame::onNumber)
EVT_BUTTON(ID_4,CalcFrame::onNumber)
EVT_BUTTON(ID_5,CalcFrame::onNumber)
EVT_BUTTON(ID_6,CalcFrame::onNumber)
EVT_BUTTON(ID_7,CalcFrame::onNumber)
EVT_BUTTON(ID_8,CalcFrame::onNumber)
EVT_BUTTON(ID_9,CalcFrame::onNumber)

EVT_BUTTON(ID_ADD,CalcFrame::onAction)
EVT_BUTTON(ID_SUS,CalcFrame::onAction)
EVT_BUTTON(ID_MUL,CalcFrame::onAction)
EVT_BUTTON(ID_DIV,CalcFrame::onAction)
EVT_BUTTON(ID_EQU,CalcFrame::onAction)
EVT_BUTTON(ID_DOT,CalcFrame::onAction)

EVT_MENU(wxID_EXIT, CalcFrame::Quit)
EVT_MENU(wxID_ABOUT, CalcFrame::About)

END_EVENT_TABLE()
