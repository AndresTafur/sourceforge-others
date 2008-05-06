#include <iostream>

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/html/htmlwin.h>
#include "ControlCenterFrame.cpp"


/**  Esta es la clase principal en la cual se inicializa la interface wxWidgets
*    y se muestra la correspondiente ventana principal.
*/
class MyApp: public wxApp
{

/**  Metodo en el cual se crea el nuevo objeto ControlCenterFrame (el cual es una ventana)
 *    y se muestra la correspondiente ventana principal.
 */
   bool OnInit()
    {
     wxString str;
     ControlCenterFrame *frame;

      ::wxInitAllImageHandlers();

      str << this->argv[0];

      str   = str.BeforeLast( '/'); 
      frame = new ControlCenterFrame(wxT("Centro de Control"),wxPoint(50,50),wxSize(450,340), str);

      frame->Show(TRUE);
      this->SetTopWindow(frame);

    return TRUE;
    }

};

IMPLEMENT_APP(MyApp)

