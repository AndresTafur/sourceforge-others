#include "WhiteHawkNetAddress.h"


   
    WhiteHawkNetAddress::WhiteHawkNetAddress(std::string ip,int port)
    {
        if( !ip.empty())    
            SetIpAddress(ip);
        else
            SetIpAddress("127.0.0.1");
        
        if( port >= 0) 
            SetPort(port);
        else
            SetPort(6000);
        address.sin_family  = AF_INET;
    }
    
    void WhiteHawkNetAddress::SetPort(int port)
    {
        address.sin_port = htons(port);
    }
    
    void  WhiteHawkNetAddress::SetIpAddress(std::string host)
    {
	struct hostent *remote;

	#ifdef WIN32
        WSADATA wsaData;
        WSAStartup(MAKEWORD(1, 1), &wsaData);
	#endif
     
            remote = gethostbyname( host.c_str() );
        
            address.sin_addr.s_addr =  ((struct in_addr *)remote->h_addr)->s_addr;

	   #ifdef WIN32
            WSACleanup();
           #endif
    }
    
    int WhiteHawkNetAddress::GetPort()
    {
        return ntohs(address.sin_port);
    }
    
     struct  sockaddr_in WhiteHawkNetAddress::GetAddress()
     {
        return address;
     }
    
    std::string WhiteHawkNetAddress::GetIpAddress()
    {
        return inet_ntoa(address.sin_addr);    
    }
    
    std::string WhiteHawkNetAddress::ResolveIP(std::string host)
    {
        struct hostent *remote;
        struct  sockaddr_in buff;

	#ifdef WIN32
        WSADATA wsaData;
        WSAStartup(MAKEWORD(1, 1), &wsaData);
	#endif
        
//            remote = gethostbyname( host.c_str() );    
            buff.sin_addr.s_addr = ((struct in_addr *)remote->h_addr)->s_addr;

	    #ifdef WIN32
            WSACleanup();
	    #endif
         return inet_ntoa(buff.sin_addr);
    }
