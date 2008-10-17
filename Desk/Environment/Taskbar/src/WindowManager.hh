#ifndef _WINDOW_MANAGER_
#define _WINDOW_MANAGER_

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <string>

class WindowManager
{
protected:

        WindowManager();

public:


        static int errorHandler(Display *dsp, XErrorEvent *err);

        static WindowManager* getInstance();

		unsigned long queryManager(Atom &property, Atom type, void* data );

		unsigned long queryManager(Window &window,Atom &property, Atom type, void* data );

		void sendToManager(Atom &property,int data1, int data2, int data3, int data4);

		void sendToManager(Window window, Atom property,int data1, int data2, int data3, int data4);

		unsigned long screenWidth();

		unsigned long screenHeight();

        Display* getDisplay();

        Atom getAtom(std::string atName);

        int getScreenNum();

        Window getRoot();

        static void destroy();

        ~WindowManager();

protected:

static WindowManager *sm_instance;
Display *m_display;
Screen	*m_scr;
Window  m_root;
int     m_scrNum;
};

#endif
