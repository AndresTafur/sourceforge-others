#ifndef _LOGINLISTENER_
#define _LOGINLISTENER_

#include <Ogre.h>
#include <OgreOde_Prefab.h>
#include <list>


#include "ApplicationFrameListener.h"
#include "GameStaticPhysicObject.h"


/**
 * Login Frame listener. Represents the listener of the login scene.
 */
class LoginListener : public ApplicationFrameListener
{
public:

    /**
     * Default constructor.
     * @param win Render window.
     * @param cam Current camera.
     * @param time_step time of run.
     * @param world Physics world.
     */
    LoginListener(RenderWindow* win, Camera* cam,Real time_step,OgreOde::World *world,Ogre::SceneManager *sm);


    /**
     *  Called when a frame has entered.
     *  @param evt Frame information.
     *  @return True when success, false otherwise.
     */
	bool frameStarted(const FrameEvent& evt);

    /**
     *  Called when a frame has entered. Add unbuffered (non-gui) keyboard handlers here.
     *  @param evt Frame information.
     *  @return True when success, false otherwise.
     */
    bool processUnbufferedKeyInput(const FrameEvent& evt);

    /**
     *  Called when a frame has entered. Add unbuffered (non-gui) mouse handlers here.
     *  @param evt Frame information.
     *  @return True when success, false otherwise.
     */
    bool processUnbufferedMouseInput(const FrameEvent& evt);

    bool collision(Contact* contact);

    /**
     *  Default destructor.
     */
	~LoginListener();

private:

   /**
     * OgreOde Physics World.
     */
    OgreOde::World *m_world;

    /**
     *  OgreOde Physics stepper (virtual reality timing).
     */
    OgreOde::StepHandler *m_stepper;

    /**
     *  Game paused flag.
     */
    bool m_paused;

    /**
     *  Current camera.
     */
    Camera *m_cam;


    GameStaticPhysicObject *dummy;
};
#endif
