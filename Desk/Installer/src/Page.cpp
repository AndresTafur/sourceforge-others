
class Page : public wxScrolledWindow
{
public:

	  Page(wxWindow *parent) : wxScrolledWindow(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL,"")
	  {
		last = NULL;
		next = NULL;
	  }


	  Page(wxWindow *parent,Page* last, Page* next) : wxScrolledWindow(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHSCROLL|wxVSCROLL|wxTAB_TRAVERSAL,"")
	  {
		this->last = last;
		this->next = next;
	  }


	  void SetNextPage(Page* next)
	  {
		this->next = next;
		next->SetLastPage(this);
		next->Show(false);
          }

	  void SetLastPage(Page* last)
	  {
		this->last = last;
	  }


	  Page* GetNextPage()
	  {
		return next;
	  }

	  Page* GetLastPage()
	  {
		return last;
	  }


	  bool isFirst()
	  {
		if( last )
		  return false;
	    return true;
	  }


	  bool isLast()
	  {
		if( next )
		  return false;
	    return true;
	  }


	  virtual void OnPresent() = 0;

protected:
Page *next;
Page *last;

};
