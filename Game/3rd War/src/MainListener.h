#ifndef _MAINLISTENER_
#define _MAINLISTENER_

#include <OgreOde_Prefab.h>
#include "ApplicationFrameListener.h"
#include "player/PlayerTruck.h"
#include "Truck.h"
#include <list>



class MainListener : public ApplicationFrameListener
{
public:

    MainListener(RenderWindow* win, Camera* cam,Real time_step,Root* root,OgreOde::World *world);

	~MainListener();

	bool frameStarted(const FrameEvent& evt);

	void addTruck(Truck *truck){ m_trucks.push_back(truck); }

    bool processUnbufferedKeyInput(const FrameEvent& evt);

    bool processUnbufferedMouseInput(const FrameEvent& evt);


private:

    OgreOde::World *_world;
    OgreOde::StepHandler *_stepper;


    char _drive;
    bool m_paused;
    Camera *m_cam;
    std::list<Truck*> m_trucks;

};
#endif
