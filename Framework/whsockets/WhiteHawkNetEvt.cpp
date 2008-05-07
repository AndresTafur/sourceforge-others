#include "WhiteHawkNetEvt.h"


      WhiteHawkNetEvt::WhiteHawkNetEvt(WhiteHawkNetData data, int type) : WhiteHawkNetObject()
      {
         this->type = type;   
         this->data = data;
      }
 

      WhiteHawkNetData WhiteHawkNetEvt::GetData()
      {
         return data;      
      }
      
      int WhiteHawkNetEvt::GetId()
      {
         return type;
      } 
      
      void WhiteHawkNetEvt::SetData(WhiteHawkNetData data)
      {
         this->data = data;
      }

      void WhiteHawkNetEvt::SetId(int type)
      {
         this->type = type; 
      }


