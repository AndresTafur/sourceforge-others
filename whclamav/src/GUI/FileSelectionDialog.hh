#include <wx/wx.h>
#include <wx/dirctrl.h>

#ifndef _FILESELECTIONDIALOG_HH_
#define _FILESELECTIONDIALOG_HH_


class FileSelectionDialog : public wxDialog
{
public:
        FileSelectionDialog(wxWindow *parent);


        wxString getFullPath();


protected:
wxGenericDirCtrl *browser;
};




#endif // _FILESELECTIONDIALOG_HH_
