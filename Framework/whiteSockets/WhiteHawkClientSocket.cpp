#include "WhiteHawkClientSocket.h"


    WhiteHawkClientSocket::WhiteHawkClientSocket(WhiteHawkClientSocket *previous,WhiteHawkClientSocket *next) : WhiteHawkNetClientStream()
    {
        this->before = previous;
        this->after  = next;
        clientID = 0;
    }


    void WhiteHawkClientSocket::Propagate(std::string data)
    {
        if( before != NULL)
            before->Propagate( data );

       this->Send(data);
    }    
    
    void WhiteHawkClientSocket::Propagate(WhiteHawkNetData data)
    {
        if( before != NULL)
            before->Propagate( data );
       
       this->Send(data);
    }
    
    void WhiteHawkClientSocket::PropagateTo(std::string data, long id)
    {
        if( NULL != before )
        {
            if( clientID != id)
                before->Propagate( data );
            else
                this->Send(data);
        }
    }

    void WhiteHawkClientSocket::PropagateTo(WhiteHawkNetData data, long id)
    {
        if( NULL != before )
        {
            if( clientID != id)
                before->Propagate( data );
            else
                this->Send(data);
        }
    }
  
     void WhiteHawkClientSocket::PropagateEx(std::string data, long id)
    {
        if( NULL != before )
        {
                before->PropagateEx( data, id );
                if( clientID != id)
                    Send(data);
        }
    }

    void WhiteHawkClientSocket::PropagateEx(WhiteHawkNetData data, long id)
    {
        if( NULL != before )
               before->PropagateEx( data, id );
                if( clientID != id)
                    Send(data);
    }   

    WhiteHawkClientSocket* WhiteHawkClientSocket::GetNext()
    {
        return after;    
    }

    WhiteHawkClientSocket* WhiteHawkClientSocket::GetPrevious()
    {
        return before;
    }
    
    void WhiteHawkClientSocket::SetNext(WhiteHawkClientSocket *next)
    {
        this->after = next;
    }

    void  WhiteHawkClientSocket::SetPrevios( WhiteHawkClientSocket *previous)
    {
        this->before = previous;
    }


    void WhiteHawkClientSocket::ifClosed()
    {
        this->before->after = after;
        this->after->before = before;
        closesocket(handler);
    }

    void WhiteHawkClientSocket::OnConnect(WhiteHawkNetEvt evt)
    {

    }
    
    void WhiteHawkClientSocket::OnDisconnect(WhiteHawkNetEvt evt){}
    void WhiteHawkClientSocket::OnError(WhiteHawkNetEvt evt)
    {
                std::cout << "WhiteHawkServerError: " << evt.GetId() << "[ " << evt.GetData() << " ]" << std::endl;
    }
    
    void WhiteHawkClientSocket::OnDataArrival(WhiteHawkNetEvt evt){}
    void WhiteHawkClientSocket::OnDataSent(WhiteHawkNetEvt evt){}
    void WhiteHawkClientSocket::OnClose(WhiteHawkNetEvt evt){}

