#ifndef _LOGINLISTENER_
#define _LOGINLISTENER_

#include <OgreOde_Prefab.h>
#include "ApplicationFrameListener.h"
#include "player/PlayerTruck.h"
#include "Truck.h"
#include <list>



class LoginListener : public ApplicationFrameListener
{
public:

    LoginListener(RenderWindow* win, Camera* cam,Real time_step,OgreOde::World *world);

	~LoginListener();

	bool frameStarted(const FrameEvent& evt);

//	void addTruck(Truck *truck){ m_trucks.push_back(truck); }

    bool processUnbufferedKeyInput(const FrameEvent& evt);

    bool processUnbufferedMouseInput(const FrameEvent& evt);


private:

    OgreOde::World *m_world;
    OgreOde::StepHandler *m_stepper;

    bool m_paused;
    Camera *m_cam;
//    std::list<Truck*> m_trucks;

};
#endif
