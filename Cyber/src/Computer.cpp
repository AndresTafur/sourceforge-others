#include "WhiteHawkThread.h"


class Computer : public ComputerPanel, public WhiteHawkThread
{
public:
    
      Computer(wxWindow *parent,wxString pcName,wxListCtrl *msg) : ComputerPanel(parent, pcName, msg )
      {
      }
  
   
  
      void StartCount()
      {
        wxString  str;
        char string[80];
             
          init = time(NULL);  
          ptr  = localtime(&init);
          
          strftime( string, 80, "%H:%M:%S", ptr );
          str << string;
          
          stctr->SetValue(str); 
          this->WhiteHawkThread::Create();  

      }
    
      void ThreadRoutine()
      {
         char buff[30];
         char pBuff[30];
         int hour;
         int mins;
         unsigned int price;
           
                        
         while(true)
         {   
            wxString  str;
            wxString str2;
            
            curr = time(NULL);
            secs = (int) difftime(curr, init);
            
            for( hour =0; secs >= 3600; hour++)
                    secs -=3600; 
                 
            for( mins=0; secs >= 60; mins++)
                    secs -=60;
     
            if( (mins == 30 && secs == 0) || (mins==0 && hour != 0 && secs == 0) )
            {
                str = pcName + wxT(" acaba de completar ");
                
                if( hour == 1)
                  str << wxT("1 hora ");
                else if( hour > 1)
                  str << hour << wxT(" horas ");
                
                if( mins != 0)
                {  
                    if( hour != 0)
                        str << wxT("y");
                    str << wxT(" 30 minutos");
                }
                    
                if( msg->GetItemCount() >= 8)
                    msg->DeleteAllItems();
                    
                msg->InsertItem( msg->GetItemCount(),str);
                str = wxT("");
            }
                            
            price = (hour*1000);
            price += (mins*17);
            
              
            if( price % 50 != 0)
            {
              int tmp = (int) (price/100); 
              tmp *= 100;
              
                if(  (price-tmp) > 30 )
                    price = tmp + 50;
                else
                    price = tmp;
            }

             if( price < 300)
                price = 300; 


            sprintf(buff,"%2.2i:%2.2i:%2.2i",hour,mins,secs);
            sprintf(pBuff,"$%i",price);

            str  << buff;
            str2 << pBuff;
            
            endctr->SetLabel(str);
            val->SetLabel(str2);
            
            if( !check->GetValue())
                if( strcmp( buff, rest->GetValue().ToAscii()) == 0 )
                    (new wxMessageDialog(this, pcName + wxT(" termino su tiempo, valor total ") + pBuff,wxT("Tiempo terminado"),wxOK|wxICON_INFORMATION))->ShowModal();
  
            T_Sleep(1000);
        }
      }  
      
      
       void onStop()
       {
            this->Terminate();
       } 
        
               
       void onStart()
       {
                StartCount(); 
       }

protected:
time_t init;
time_t curr;
struct tm *ptr;
int secs; 
};
