#include "WhiteHawkNetObject.h"
#include "WhiteHawkNetAddress.h"

#ifndef _WhiteHawkNetData_
#define _WhiteHawkNetData_

class WhiteHawkNetData : public std::string, public WhiteHawkNetObject
{
public:
    
     WhiteHawkNetData(std::string data = "");
     
     void operator<<(WhiteHawkNetData str);
     void operator<<(std::string str);


    

};
#endif
