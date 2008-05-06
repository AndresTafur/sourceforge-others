#include "Clock.hh"


	TaskTime::TaskTime(wxButton *txt)
	{
		this->txt = txt;

	  	txt->SetLabel( getTime() );

	}

	void TaskTime::ThreadRoutine()
	{
		while(true)
		{
            wxMutexGuiEnter();
		  	txt->SetLabel(getTime() );
		  	wxMutexGuiLeave();
			this->T_Sleep(600);
		}
	}

	void TaskTime::onTerminate()
	{

	}

	wxString TaskTime::getTime()
	{
	  wxString str;
	  time_t current;
  	  char cad[80];
  	  struct tm *tmPtr;

		  current = time(NULL);
		  tmPtr = localtime(&current);
	  	  strftime( cad, 80, "%I:%M", tmPtr );
		  str << cad;
	  return cad;
	}


	wxString TaskTime::getDate()
	{
	  wxString str;
	  char cad[80];
	  time_t current;
  	  struct tm *tmPtr;

		  current = time(NULL);
		  tmPtr = localtime(&current);
	  	  strftime( cad, 80, "%A, %d de %B", tmPtr );
		  str << cad;
	  return str;
	}




    Clock::Clock(wxWindow *parent, wxWindowID id) : wxButton(parent,id,wxT("00:00"),wxDefaultPosition, wxSize(50,25),wxBU_EXACTFIT|wxNO_BORDER, wxDefaultValidator,wxT(""))
	{
		time = new TaskTime(this);
		time->Create();

		this->SetToolTip(  time->getDate()  );
		this->Fit();

	}
