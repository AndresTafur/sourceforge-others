
#ifndef _TASK_TIME_
#define _TASK_TIME_

#include <Thread.hh>
#include <wx/wx.h>



class TaskTime : public WhiteHawkSystem::Thread
{
public:

	TaskTime(wxButton *txt);

	void run();
	void onTerminate();

	wxString getTime();

	wxString getDate();


private:
wxButton *txt;
};




class Clock : public wxButton
{
public:

Clock(wxWindow *parent, wxWindowID id);


protected:
TaskTime *time;
};

#endif
