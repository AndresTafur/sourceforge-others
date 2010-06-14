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


    bool frameStarted(const FrameEvent& evt);

    /**
     * Frees every resource used. Called by Application when finished.
     * @see Application.
     */

    void destroyScene();

 private:


  /**
   * Terrain object.
   */
  GameObject *m_ground;

  /**
   * Physics world.
   */
  OgreOde::World *m_world;

  /**
   * Collision detector (of m_ground).
   */
  OgreOde::TriangleMeshGeometry *m_track;

  /**
   * Physics world timing.
   */
  Real m_time_step;

  /**
    * Trajectory
    */
  std::vector<Vector3> m_points;


  /**
    * Current trajectoy object.
    */
  unsigned int m_currPoint;


  float m_factor;

  bool m_lauched;

  bool m_change;

  float val;

  float m_farClip;

};
#endif
