#ifndef _PLAYER_TRUCK_H_
#define _PLAYER_TRUCK_H_

#include <time.h>
#include "PlayerFlag.h"

#include "../Truck.h"
#include "../GameObject.h"
#include "../GameStaticPhysicObject.h"


class PlayerTruck : public Truck, public OgreOde::CollisionListener
{
  public:

        PlayerTruck(Camera* cam,OgreOde::World *world,OIS::Keyboard *key);

        bool collision(OgreOde::Contact* contact);

        void toggle(const FrameEvent& evt);

        void frameStarted(const FrameEvent& evt);


private:

 OIS::Keyboard *m_keyboard;
 Ogre::Vector3 prevPos;
 Camera *m_camera;
 int m_gear;
 unsigned short m_flags;
 bool m_win;
 bool m_lose;
 float m_volS;

};
#endif
