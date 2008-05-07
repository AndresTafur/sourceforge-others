#include "config.h"

#ifndef _WhiteHawkNetAddress_
#define _WhiteHawkNetAddress_

class WhiteHawkNetAddress
{
public: 
    
    WhiteHawkNetAddress(std::string ip = "127.0.0.1",int port = 6000);
    
    void SetPort(int port);
    
    void SetIpAddress(std::string ip);
    
    int GetPort();
    
    std::string ResolveIP(std::string host);
    struct  sockaddr_in GetAddress();
    std::string GetIpAddress();
    
protected:    
struct  sockaddr_in address;
};

#endif
