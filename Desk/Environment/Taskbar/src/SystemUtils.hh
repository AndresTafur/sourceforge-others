
#ifndef _SYSTEM_UTILS_
#define _SYSTEM_UTILS_

#include <X11/Xlib.h>
#include <list>

class SystemUtils
{
public:

		SystemUtils();

        static int errorHandler(Display *dsp, XErrorEvent *err);


		unsigned long queryManager(Atom property, Atom type, void* data );
		unsigned long queryManager(Window window,Atom property, Atom type, void* data );


		void sendToManager(Atom property,int data1, int data2, int data3, int data4);
		void sendToManager(Window window, Atom property,int data1, int data2, int data3, int data4);


		int getDesktops();
		int getCurrentDesk();


		Window getActiveWindow();

		char* getWindowName(Window window);

        int getWndDesktop(Window window);

		std::list<Window> getWindows(int *num);

        Atom getAtom(const char *atmnme);


		void setCurrentDesktop(int num);

		void setActiveWindow(Window window);



		bool isNormalWnd(Window window);

		void iconifyWindow(Window window);

		void closeWindow( Window window);

        void startMoveWindow( Window window);

        void startSizeWindow( Window window);


		unsigned long screenWidth();

		unsigned long screenHeight();

public:

         Atom getCurrDeskA();

         Atom getNetDeskA();

         Atom getWindowListA();

         Atom getActiveWindowA();

protected:
Display *display;
Screen	*scr;
Window  root;
int curr_desk;
int desk_num;
int scr_num;

Atom m_skiptask;
Atom m_state;
Atom m_totdesk;
Atom m_curdesk;
Atom m_netdesk;
Atom m_deskname;

Atom m_wtype;
Atom m_wdlg;
Atom m_wdock;
Atom m_wnorm;
Atom m_wactive;
Atom m_wlist;
};
#endif
