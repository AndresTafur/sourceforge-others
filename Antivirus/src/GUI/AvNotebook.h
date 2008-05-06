
#include <wx/aui/auibook.h>

#include "AvPanel.hh"
#include "StatusPanel.hh"
#include <Clamav.hh>

#ifndef _AVNOTEBOOK_H_
#define _AVNOTEBOOK_H_



class AvNotebook : public wxAuiNotebook
{
public:
    AvNotebook(wxWindow *parent, wxAnimationCtrl *load,int id);

    void loadDb();

    void insertStatus();

    void insertScan();



protected:
AvPanel	      *scan;
StatusPanel   *status;
WhiteHawkClamav::Clamav *clammgr;
wxAnimationCtrl *load;
};



#endif // AVNOTEBOOK_H_INCLUDED
