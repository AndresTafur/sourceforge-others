#include "PlayerFlag.h"



   PlayerFlag::PlayerFlag( Ogre::SceneManager *sceneMgr, double secs, const Ogre::Vector3 &vect) : GameObject(sceneMgr,"Flag.mesh")
   {
        this->getNode()->setPosition(vect);
        m_secs = secs;
   }

  std::string PlayerFlag::getFormatedTime()
  {
    std::string time;
    int dfTimeSec, dfTimeMin = 0;
    char text[30];

            dfTimeSec = getSecs();


            while( dfTimeSec >= 60)
            {
                dfTimeSec -=60;
                ++dfTimeMin;
            }

            sprintf(text,"Time:  %i:%i",dfTimeMin,dfTimeSec);
            time = text;

      return  time;
    }
