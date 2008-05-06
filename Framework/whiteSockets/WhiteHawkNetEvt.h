#include "WhiteHawkNetObject.h"
#include "WhiteHawkNetData.h"

#ifndef _WhiteHawkNetEvt_
#define _WhiteHawkNetEvt_

enum 
{
    NET_SOCKET_ERROR = 9000,
    NET_REMOTE_ERROR,
    NET_SEND_ERROR,
    NET_REC_ERROR,
    NET_CONNECT_ERROR,
    NTE_BIND_ERROR,
    NET_LISTEN_ERROR,
    
    
    NET_EVT_DISCONNECT,
    NET_EVT_CONNECT,
    NET_EVT_LISTEN,
    NET_EVT_DATAARRIVAL,
    NET_EVT_DATASENT,
    NET_EVT_ERROR,
};  



class WhiteHawkNetEvt : public WhiteHawkNetObject
{
public:
    
      WhiteHawkNetEvt(WhiteHawkNetData data, int type = NET_EVT_ERROR);

      WhiteHawkNetData GetData();
      int GetId();
      void SetData(WhiteHawkNetData data);
      void SetId(int type);

protected:    
int type;    
WhiteHawkNetData data;
};

#endif
