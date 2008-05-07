#include "WhiteHawkThread.h"
#include "WhiteHawkNetServerListener.h"
#include "WhiteHawkNetSocketStream.h"
#include "WhiteHawkClientSocket.h"


#ifndef _WhiteHawkNetServerStream_
#define _WhiteHawkNetServerStream_

class WhiteHawkNetServerStream : public WhiteHawkNetSocketStream
{
public:    
    
        WhiteHawkNetServerStream();
        
        void Send(std::string str);
        void Send(WhiteHawkNetData str);
      
        void SendTo(std::string str, long id);
        void SendTo(WhiteHawkNetData str, long id);
        
      
        void SendEx(std::string str, long id);
        void SendEx(WhiteHawkNetData str, long id);  

        void operator << (std::string str);
        void operator << (WhiteHawkNetData str);

protected:
WhiteHawkClientSocket   *list;   
    
};
#endif
