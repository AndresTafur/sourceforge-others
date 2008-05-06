#ifndef _FACTURER_
#define _FACTURER_

#include <wx/wx.h>
#include <wx/statline.h>

#include "FactureGrid.hh"
#include "InventoryFinderDlg.hh"

enum
{
  FACT_CREDIT = 0,
  FACT_GRID,
  FACT_INS,
  FACT_DEL,
  FACT_PRINT,
  FACT_INV,
  FACT_VIEW,
  FACT_FORMAT,
  FACT_TOT,
  FACT_NUM,
  FACT_DATE,

};


class Facturer : public wxFrame
{

public:

    Facturer(wxWindow *parent);


    void onDelete(wxCommandEvent &evt);

    void onInsert(wxCommandEvent &evt);

    void onView(wxCommandEvent &evt);

    void onSubTotal(wxGridEvent &evt);

    void onNumberChange(wxCommandEvent &evt);

    void onSearch(wxCommandEvent &evt);

protected:
FactureGrid  *m_grid;
wxStaticText *m_tot;
wxTextCtrl   *m_factnum;

protected:
DECLARE_EVENT_TABLE();
};

#endif
