#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/splitter.h>
#include <wx/grid.h>

#include "rcids.hh"
#include "ComputerPanel.cpp"
#include "Computer.cpp"
#include "CyberFrame.cpp"



class Cyber : public wxApp
{
public:

    bool OnInit()
    {
        CyberFrame  *frame = new CyberFrame();
        
        
            frame->Show();
          
        return true;
    }      

    
};
IMPLEMENT_APP(Cyber)
