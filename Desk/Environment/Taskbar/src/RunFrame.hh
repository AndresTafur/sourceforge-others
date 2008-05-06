#include <wx/wx.h>

#ifndef _RUN_PANEL_
#define _RUN_PANEL_


enum
{
   ID_BRW,
   ID_PTH,

};

class RunPanel : public wxPanel
{
public:

        RunPanel(wxWindow *parent,wxString &str);

        void exec(wxString str);

        void onAccept(wxCommandEvent &evt);

        void onCancel(wxCommandEvent &evt);

        void onBrowse(wxCommandEvent &evt);



private:
wxTextCtrl *path;

DECLARE_EVENT_TABLE();

};


class RunFrame : public  wxDialog
{
public:

        RunFrame(wxString &str);

};
#endif
