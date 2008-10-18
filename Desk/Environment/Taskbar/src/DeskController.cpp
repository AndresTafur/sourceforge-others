#include "DeskController.hh"
#include "WindowManager.hh"

DeskController* DeskController::sm_instance = NULL;

        DeskController::DeskController()
        {
			m_totdeskA  = WindowManager::getInstance()->getAtom("_NET_NUMBER_OF_DESKTOPS");
			m_curdeskA  = WindowManager::getInstance()->getAtom("_NET_CURRENT_DESKTOP");
			m_desknameA = WindowManager::getInstance()->getAtom("_NET_DESKTOP_NAMES");
			m_netdeskA  = WindowManager::getInstance()->getAtom("_NET_WM_DESKTOP");
			m_showDeskA = WindowManager::getInstance()->getAtom("_NET_SHOWING_DESKTOP");
        }


        DeskController* DeskController::getInstance()
        {
                if( ! sm_instance)
                    sm_instance = new DeskController();
            return sm_instance;
        }


		int DeskController::getDesktops()
		{
		  unsigned long *num_desktops;
		  unsigned long deskNum;

			WindowManager::getInstance()->queryManager(m_totdeskA,XA_CARDINAL,&num_desktops);
			deskNum = (*num_desktops);

            if(num_desktops != NULL)
                XFree(num_desktops);

		return deskNum;
		}


		int DeskController::getCurrentDesk()
		{
		  unsigned long *desktop;
		  unsigned long currDesk;

	 		 WindowManager::getInstance()->queryManager(m_curdeskA,XA_CARDINAL,&desktop);

			   currDesk = (*desktop);

			if(desktop != NULL)
                XFree(desktop);

		return currDesk;
		}


		void DeskController::setCurrentDesktop(int num)
		{
		    WindowManager::getInstance()->sendToManager( m_curdeskA, num, 0, CurrentTime, 0);
		}


		void DeskController::showDesktop(bool val)
		{
            WindowManager::getInstance()->sendToManager(m_showDeskA,val,0,0,0);
		}

        bool DeskController::isVisible()
        {
		  unsigned long *desktop;
		  unsigned int currDesk;

	 		 WindowManager::getInstance()->queryManager(m_showDeskA,XA_CARDINAL,&desktop);

			   currDesk = (*desktop);

			if(desktop != NULL)
                XFree(desktop);

		return currDesk;

        }
