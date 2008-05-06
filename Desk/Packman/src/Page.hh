
#ifndef _PAGE_
#define _PAGE_

#include <wx/wx.h>

class Page : public wxPanel
{
public:

	  Page(wxWindow *parent);

	  Page(wxWindow *parent,Page* last, Page* next);


	  void SetNextPage(Page* next);

	  void SetLastPage(Page* last);


	  Page* GetNextPage();

	  Page* GetLastPage();


	  bool isFirst();


	  bool isLast();


	  virtual void OnPresent() = 0;

protected:
Page *next;
Page *last;

};
#endif
