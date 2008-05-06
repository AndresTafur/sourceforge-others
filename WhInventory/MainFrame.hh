#ifndef _MAIN_FRAME_
#define _MAIN_FRAME_

#include <wx/wx.h>

#include "MainDialog.hh"
#include "Facturer.hh"

enum
{

  ID_FILE_QUIT = 100,
  ID_FILE_PRINT_FC,
  ID_TOOL_FACTURING,
  ID_TOOL_INVENTORY,

  ID_TOOL_CFG_FACT,
  ID_TOOL_CFG_PROG,
  ID_TOOL_CFG_INV,

};



class MainFrame : public wxFrame
{
public:

        MainFrame();

        void runMainDlg();

       void facturer(wxCommandEvent &evt);

       void inventory(wxCommandEvent &evt);

       void buys(wxCommandEvent &evt);

protected:
DECLARE_EVENT_TABLE()

};
#endif



