#include "Clock.hh"


	TaskTime::TaskTime(wxButton *txt)
	{
		this->txt = txt;

	  	txt->SetLabel( getTime() );
	}

	void TaskTime::run()
	{
		while(true)
		{
            wxMutexGuiEnter();
		  	txt->SetLabel(getTime() );
		  	wxMutexGuiLeave();
			WhiteHawkUtil::Thread::sleep(600);
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
		  str << wxString::FromAscii(cad);
	  return wxString::FromAscii(cad);
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
		  str << wxString::FromAscii(cad);
	  return str;
	}




    Clock::Clock(wxWindow *parent, wxWindowID id) : wxButton(parent,id,wxT("00:00"),wxDefaultPosition, wxSize(50,25),wxBU_EXACTFIT|wxNO_BORDER, wxDefaultValidator,wxT(""))
	{
		time = new TaskTime(this);
		time->startThread();

		this->SetToolTip(  time->getDate()  );
		this->Fit();

	}
