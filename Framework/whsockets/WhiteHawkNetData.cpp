#include "WhiteHawkNetData.h"


     WhiteHawkNetData::WhiteHawkNetData(std::string data) : std::string(data),WhiteHawkNetObject( "NetData")
     {}
     
     
     void WhiteHawkNetData::operator<<(WhiteHawkNetData str)
     {
       this->append(str);
     }
 
     void WhiteHawkNetData::operator<<(std::string str)
     {
         this->append(str);
     }
