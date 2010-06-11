#include "PlayerTruck.h"
#include <stdlib.h>

PlayerTruck::PlayerTruck(Camera* cam,OgreOde::World *world,OIS::Keyboard *key)  : Truck(world)
{
PlayerFlag *flag;

        m_volS = 1;
        m_keyboard = key;
        m_camera = cam;


        if( !world->getSceneManager()->hasParticleSystem("Smoke"))
            _pSys = world->getSceneManager()->createParticleSystem("Smoke", "Examples/Smoke");
        else
        _pSys = world->getSceneManager()->getParticleSystem("Smoke");

        _pSys->getEmitter(0)->setEnabled(false);
        _pSys->getEmitter(1)->setEnabled(false);

        _vehicle->getSceneNode()->attachObject(_pSys  );
        _vehicle->setPosition(Ogre::Vector3(-400,-12,100));
        world->setCollisionListener(this);
        m_gear = 1;


        flag = new PlayerFlag( world->getSceneManager(), 10.0,Ogre::Vector3(-400,-13,209));m_vectors.push_back(flag);
        flag = new PlayerFlag( world->getSceneManager(), 10.0,Ogre::Vector3(-337,-13,374));m_vectors.push_back(flag);
        flag = new PlayerFlag( world->getSceneManager(), 10.0,Ogre::Vector3(7,-13,273));m_vectors.push_back(flag);
        flag = new PlayerFlag( world->getSceneManager(), 10.0,Ogre::Vector3(238,-13,280));m_vectors.push_back(flag);
        flag = new PlayerFlag( world->getSceneManager(), 10.0,Ogre::Vector3(470,-13,141));m_vectors.push_back(flag);
        flag = new PlayerFlag( world->getSceneManager(), 10.0,Ogre::Vector3(486,-13,-406));m_vectors.push_back(flag);
        flag = new PlayerFlag( world->getSceneManager(), 10.0,Ogre::Vector3(367,-13,-534));m_vectors.push_back(flag);
        flag = new PlayerFlag( world->getSceneManager(), 10.0,Ogre::Vector3(73,-13,-501));m_vectors.push_back(flag);
        flag = new PlayerFlag( world->getSceneManager(), 10.0,Ogre::Vector3(-403,-13,-198));m_vectors.push_back(flag);

        iter = m_vectors.begin();
        m_flags = m_vectors.size();
        m_win  = false;
        m_lose = false;

}


bool PlayerTruck::collision(OgreOde::Contact* contact)
{
	if(!OgreOde_Prefab::Vehicle::handleTyreCollision(contact))
	{
		contact->setBouncyness(0.3);
		contact->setCoulombFriction(15.0);
    }

	return true;
}



 void PlayerTruck::toggle(const FrameEvent& evt)
 {
      if( m_keyboard->isKeyDown(OIS::KC_R) && m_vectors.size() != m_flags)
          _vehicle->setPosition( prevPos + Ogre::Vector3(0,10,0)  );

      if( m_keyboard->isKeyDown( OIS::KC_Z) && m_gear >= 0 )
      {
      }
      else if(m_keyboard->isKeyDown( OIS::KC_A) && m_gear < 1)
      {

      }
/*
      if( m_keyboard->isKeyDown( OIS::KC_O))
      {
          FILE *file = fopen("Trees.dat","a");

            if(file)
            {
                fprintf(file,"[%i,%i]\n",  static_cast<int>(_vehicle->getPosition().x),static_cast<int>(_vehicle->getPosition().z));
                fprintf(stderr,"[%i,%i]\n",  static_cast<int>(_vehicle->getPosition().x),static_cast<int>(_vehicle->getPosition().z));
                fclose(file);
            }
      }*/


      if( m_keyboard->isKeyDown(OIS::KC_UP))
      {

      }
      else
      {


      }
 }



void PlayerTruck::frameStarted(const FrameEvent& evt)
{
const Ogre::Real followFactor = 0.2;
const Ogre::Real camHeight = 2.0;
const Ogre::Real camDistance = 8.0;
const Ogre::Real camLookAhead = 8.0;
const Ogre::Real frameTime = evt.timeSinceLastFrame;

Vector3 toCam;
Ogre::Vector3 vect;
Ogre::Vector3 des,orient;
Ogre::Quaternion q;

                vect = _vehicle->getPosition();

                if(! m_vectors.empty())
                {
                    des = (*iter)->getNode()->getPosition();

                    if( des.x - 10 < vect.x&& des.x+10 > vect.x && des.z < vect.z+10 && des.z > vect.z-10 )
                    {
                       float  extra = 0;

                            prevPos = des;
                            (*iter)->getNode()->detachAllObjects();

                            if( (*iter)->getSecs() > 0 && m_vectors.size() != m_flags)
                               extra = (*iter)->getSecs();

                            delete (*iter);
                            m_vectors.erase(iter);

                            if(!m_vectors.empty() )
                            {
                                iter = m_vectors.begin();
                                (*iter)->addSecs(extra);
                                (*iter)->startTime();
                            }
                            else
                            {
                                m_win = true;
                            }

                    }
                 }

                if( !m_win && !m_lose )
                {
                  short steer = (-1)*m_keyboard->isKeyDown(OIS::KC_LEFT) + m_keyboard->isKeyDown(OIS::KC_RIGHT);
                  short accel= m_keyboard->isKeyDown(OIS::KC_UP)*m_gear;


                       if( !m_vectors.empty() && m_vectors.size() != m_flags )
                       {
                         std::string formatedTime = (*iter)->getFormatedTime();

                                if( (*iter)->getSecs() - 5 <= 0)
                                {
                                }

                               if( (*iter)->getSecs() <= 0)
                               {
                                 m_lose = true;
                               }
                       }


                    _vehicle->setInputs(steer,accel, m_keyboard->isKeyDown(OIS::KC_DOWN));
                    _vehicle->update(frameTime);

                    q = _vehicle->getSceneNode()->getOrientation();
                    toCam = _vehicle->getSceneNode()->getPosition();

                    toCam.y += camHeight+10;
                    toCam.z -= camDistance * q.zAxis().z;
                    toCam.x -= camDistance * q.zAxis().x;

                    m_camera->move( (toCam - m_camera->getPosition()) * followFactor );
                    m_camera->lookAt(_vehicle->getSceneNode()->getPosition() + ((_vehicle->getSceneNode()->getOrientation() * Ogre::Vector3::UNIT_Z + Ogre::Vector3(0,0.7,-0.2) ) * camLookAhead));
                }
}
