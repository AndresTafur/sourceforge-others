#include <stdio.h>
#include <X11/Xlib.h>


int main()
{
XEvent evt;

          Display *display = XOpenDisplay(NULL);
          Window  root     = XDefaultRootWindow(display);

	    XSelectInput(display, root,SubstructureNotifyMask);


            while(1)
            {

               XWindowEvent(display,root,SubstructureNotifyMask,&evt);

                switch(evt.type)
                {
                    case MapNotify:
                            fprintf(stderr,"Nueva ventana");
                          //  m_list->addWindow(evt.xmap.window,false);
                            break;

                    case DestroyNotify:
                         break;


                    case UnmapNotify:
                       break;

                 }
            }
}
