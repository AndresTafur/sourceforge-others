#include "WhiteHawkThread.h"
#include "WhiteHawkNetSocketStream.h"


#ifndef _WhiteHawkNetClientStream_
#define _WhiteHawkNetClientStream_


class WhiteHawkNetClientStream : public WhiteHawkNetSocketStream, public WhiteHawkThread
{
public:    
    
       void ThreadRoutine();
    
    
       void Send(std::string str);
       void Send(WhiteHawkNetData str);
       
       void SetId(long id);
       long GetId();
       
       void operator << (std::string str);
       void operator << (WhiteHawkNetData str);
       
protected:  
    
      virtual void ifClosed() = 0;

      
long clientID;    
    
};
#endif
