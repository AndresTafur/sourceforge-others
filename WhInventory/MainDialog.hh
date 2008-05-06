#ifndef _MAIN_DLG_
#define _MAIN_DLG_

#include <wx/wx.h>

enum
{

  ID_LIST = 1,
  ID_BTN_ACCEPT,
  ID_BTN_CANCEL,
};


class MainDialog : public wxDialog
{
public:

        MainDialog (wxFrame *parent);

        void onAccept( wxCommandEvent &evt);

        void onCancel(wxCommandEvent &evt);


protected:
    wxListBox  *caja;
    wxArrayString str;

private:
    DECLARE_EVENT_TABLE()

};
#endif
