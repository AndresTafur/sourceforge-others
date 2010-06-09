#ifndef _MAINAPP_
#define _MAINAPP_

#define dSINGLE

#include <OgreOde_Prefab.h>
#include <MyGUI.h>

#include <Application.h>
#include <GameObject.h>
#include <GameStaticPhysicObject.h>
#include <MainListener.h>


#include "Tree.h"


class MainApplication : public Application
{
public:
    MainApplication();
    ~MainApplication();

protected:

        virtual void chooseSceneManager(void);
        virtual void setupResources(void);
        virtual void createCamera(void);
        void createScene(void);
        void createFrameListener(void);
        void destroyScene();
        void createGui();
        void createNature();

protected:
    Light* m_l;
    GameObject *m_ground;


	OgreOde::World *_world;
	OgreOde_Prefab::Vehicle *_vehicle;
	OgreOde::TriangleMeshGeometry *_track;
	Real _time_step;

};
#endif

