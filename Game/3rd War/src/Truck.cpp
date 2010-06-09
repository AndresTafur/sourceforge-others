#include "Truck.h"

short Truck::sm_truckNum = 1;


Truck::Truck(OgreOde::World *world,Ogre::Vector3 vect)
{

    m_dotOgreOdeLoader = new OgreOde_Loader::DotLoader(world);
    _vehicle = static_cast <OgreOde_Prefab::Vehicle *> (m_dotOgreOdeLoader->loadObject ("truck.ogreode", "Truck"));
    _vehicle->setPosition( vect + Ogre::Vector3(15,0,20* Truck::getTruckNumber()) );
    m_acel = true;
/*    m_accelSound.open("EngineAcel.ogg");
    m_iddleSound.open("EngineIdle.ogg");

    m_accelSound.setLoop(true);
    m_accelSound.pause();
    m_accelSound.play();
    m_accelSound.pause();

    m_iddleSound.setLoop(true);bin/Release/track
    m_iddleSound.play();


   flag = new PlayerFlag( world->getSceneManager(), 10.0,Ogre::Vector3(-400,-13,209));m_vectors.push_back(flag);
   flag = new PlayerFlag( world->getSceneManager(), 10.0,Ogre::Vector3(-337,-13,374));m_vectors.push_back(flag);

   iter = m_vectors.begin();
   m_prevAng = 540;
*/
}


void Truck::setPosition( Ogre::Vector3 &vect)
{
    _vehicle->setPosition( vect);
}

void Truck::pause(bool pausa)
{
    //_pSys->setVisible(!pausa);
}

void Truck::frameStarted(const FrameEvent& evt)
{
Ogre::Vector3 vect = _vehicle->getPosition();
Ogre::Vector3 des = (*iter)->getNode()->getPosition();
Ogre::Real time = evt.timeSinceLastFrame;
Ogre::Quaternion quat;



            if( des.x < vect.x + 15 && des.x > vect.x -15 && des.z < vect.z+15 && des.z > vect.z-15 )
            {
                iter++;
                fprintf(stderr,"CHECKPOINT___________\n");
                m_prevAng = 540;
                if( iter == m_vectors.end())
                    m_acel = false;
                 des = (*iter)->getNode()->getPosition();

            }

         _vehicle->setInputs(vect.getRotationTo(des).x*1000,m_acel*0.1,!m_acel);
         _vehicle->update(time);
}

