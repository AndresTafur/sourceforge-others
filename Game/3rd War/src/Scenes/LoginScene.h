#ifndef _LOGIN_SCENE_H
#define  _LOGIN_SCENE_H

#include <Ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>


#include "GameObject.h"
#include "SceneBase.h"
#include "LoginListener.h"


/**
 * Login Scene. Manages everything about the login scene.
 * @see SceneBase
 */
class LoginScene : public SceneBase
{
 public:

    /**
     * Default constructor. Starts initial objects,Called by Application before everything.
     * @param wnd render window.
     * @see Application.
     */

    LoginScene(Ogre::RenderWindow *wnd);


    /**
     * Initializes Mygui. Starts mygui and load the the fault layout, called by Application.
     * @see Application.
     * @see Gui
     */

    void createGui();


    /**
     * Initializes all managers and listeners.
     * @see Application.
     */

    void createManagers();



    /**
     * Create camera. Create the camera and locate it within the world, also creates viewports.
     * @see Application.
     */

    void createCameras();

    /**
     * Create the scene. load every mesh and start physics, called by Application.
     * @see Application.
     */

    void createScene();

    /**
     * Manages the login scene movement frame by frame.
     */
    bool frameStarted(const FrameEvent& evt);


    /**
     * Frees every resource used. Called by Application when finished.
     * @see Application.
     */

    void destroyScene();

 private:

  /**
   * Physics world.
   */
  OgreOde::World *m_world;

  /**
   * Terrain object.
   */
  OgreOde::TriangleMeshGeometry *m_track;

  /**
   * Physics world timing.
   */
  Real m_time_step;

  /**
    * Current trajectoy object.
    */
  unsigned int m_currPoint;

  /**
   * Fade factor.
   */
  float m_factor;

  /**
   * Sacks has been moved by explosion.
   */
  bool m_lauched;

  /**
   * Camera state from running to ground.
   */
  bool m_change;

  /**
   * Camera Acceleration .
   */
  float val;

   /**
    * Far vision factor, after recovering the knowledge.
    */
  float m_farClip;

  std::vector<AnimationState*> mAnimationStates;


  GameObject *m_bullet;

};
#endif
