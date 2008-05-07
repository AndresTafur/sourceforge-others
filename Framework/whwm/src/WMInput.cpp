#include "WMInput.hh"
#include "WMInstance.hh"



    long WMInput::query(Atom property, Atom type, void* data )
    {
        return  query(WMInstance::getRoot(),property,type,data);
    }


    long WMInput::query(Window window,Atom property, Atom type, void* data )
    {
        int format;
		  unsigned long  num_items = -1;
		  unsigned long  after_bytes;
		  Atom typeret;

           XGetWindowProperty(WMInstance::getDisplay(),window,property,0,0x7fffffff,0,type,&typeret,
				&format,&num_items,&after_bytes,(unsigned char **)data);

			return num_items;
    }


