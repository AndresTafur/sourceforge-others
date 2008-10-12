
#ifndef _DESK_CONTROLLER_
#define _DESK_CONTROLLER_

#include <X11/Xlib.h>
#include <list>

class DeskController
{
protected:

		DeskController();

public:

        static DeskController* getInstance();

		int getDesktops();

		int getCurrentDesk();

		void setCurrentDesktop(int num);

        void showDesktop(bool val);


protected:
static DeskController *sm_instance;

Atom m_totdeskA;
Atom m_curdeskA;
Atom m_desknameA;
Atom m_netdeskA;
Atom m_showDeskA;
};
#endif
