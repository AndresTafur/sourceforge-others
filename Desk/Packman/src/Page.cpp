#include "Page.hh"
#include "InstallerFrame.hh"


	  Page::Page(wxWindow *parent) : wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL,"")
	  {
		last = NULL;
		next = NULL;
	  }


	  Page::Page(wxWindow *parent,Page* last, Page* next) : wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL,"")
	  {
		this->last = last;
		this->next = next;
	  }


	  void Page::SetNextPage(Page* next)
	  {
		this->next = next;
        if(next)
        {
            next->SetLastPage(this);
            next->Show(false);
        }
      }

	  void Page::SetLastPage(Page* last)
	  {
		this->last = last;
      }


	  Page* Page::GetNextPage()
	  {
		return next;
	  }

	  Page* Page::GetLastPage()
	  {
		return last;
	  }


	  bool Page::isFirst()
	  {
		if( last )
		  return false;
	    return true;
	  }


	  bool Page::isLast()
	  {
		if( next )
		  return false;
	    return true;
	  }
