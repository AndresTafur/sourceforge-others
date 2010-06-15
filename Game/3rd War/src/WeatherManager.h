#ifndef _WEATHER_MANAGER_H
#define _WEATHER_MANAGER_H

#include <Ogre.h>

/**
 * Manages the Weather.
 */
 //TODO: Termiar esto
class WeatherManager
{
private:

        WeatherManager();

public:

        static WeatherManager* getInstancePtr();

        static WeatherManager& getInstance();

        void setDarkness();

        void setFoggy();

        void setRainy();

        inline void setRenderWindow(Ogre::RenderWindow *wnd) { m_window = wnd; }

        inline void setSceneManager(Ogre::SceneManager *mgr) { m_sceneMgr = mgr; }


private:
Ogre::RenderWindow *m_window;
Ogre::SceneManager *m_sceneMgr;
static WeatherManager *sm_instance;
};


#endif
