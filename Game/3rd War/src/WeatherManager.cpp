#include "WeatherManager.h"

WeatherManager* WeatherManager::sm_instance = 0;

        WeatherManager::WeatherManager()
        {
        }


        WeatherManager& WeatherManager::getInstance()
        {
                if( !sm_instance)
                    sm_instance = new WeatherManager();
                return *sm_instance;
        }


        WeatherManager* WeatherManager::getInstancePtr()
        {
                if( !sm_instance)
                    sm_instance = new WeatherManager();
                return sm_instance;
        }


        void WeatherManager::setDarkness()
        {
          Ogre::ColourValue fadeColour(0.1, 0.1, 0.1);

            m_window->getViewport(0)->setBackgroundColour(fadeColour);
            m_sceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 1000);
            m_sceneMgr->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
        }

        void WeatherManager::setFoggy()
        {
            m_sceneMgr->setFog(Ogre::FOG_LINEAR, Ogre::ColourValue(0.8, 0.8, 0.8), 0.0, 100, 1000);
            m_sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
        }

        void WeatherManager::setRainy()
        {
          Ogre::ParticleSystem *rainPSys;

            if(!m_sceneMgr->hasParticleSystem("LoginRain"))
                rainPSys = m_sceneMgr->createParticleSystem("LoginRain", "LoginRain");
            else
                rainPSys = m_sceneMgr->getParticleSystem("LoginRain");

                  m_sceneMgr->getRootSceneNode()->attachObject(rainPSys);
        }
