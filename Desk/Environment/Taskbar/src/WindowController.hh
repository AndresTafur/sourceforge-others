
#ifndef _WINDOW_CONTROLLER_
#define _WINDOW_CONTROLLER_

#include <X11/Xlib.h>
#include <list>

class WindowController
{
protected:

		WindowController();

public:

        static WindowController* getInstance();


		Window getActiveWindow();

		char* getWindowName(Window window);

        int getWndDesktop(Window window);

		std::list<Window> getWindows(int *num);

        Atom getAtom(const char *atmnme);


		void setActiveWindow(Window window);


		bool isNormalWnd(Window window);

		void iconifyWindow(Window window);

		void closeWindow( Window window);

        void startMoveWindow( Window window);

        void startSizeWindow( Window window);


protected:
static WindowController *sm_instance;

Atom m_stateA;
Atom m_skiptaskA;
Atom m_wactiveA;
Atom m_wlistA;
Atom m_wtypeA;
Atom m_wnormA;
Atom m_wdlgA;
Atom m_wdockA;
Atom m_wcloseA;
Atom m_wmoveresA;

};
#endif
