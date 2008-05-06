#ifndef _FACTURE_GRID_
#define _FACTURE_GRID_

#include <wx/grid.h>

class FactureGrid : public wxGrid
{
public:

     FactureGrid(wxWindow *parent, int id);

    void onEnter(wxKeyEvent &evt);

protected:

DECLARE_EVENT_TABLE();
};

#endif
