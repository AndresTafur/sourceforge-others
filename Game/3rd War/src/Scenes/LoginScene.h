#ifndef _LOGIN_SCENE_H
#define  _LOGIN_SCENE_H

#include <Ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>


#include "SceneBase.h"
#include "LoginListener.h"



class LoginScene : public SceneBase
{
 public:

    LoginScene(Ogre::RenderWindow *wnd);

    void createFrameListener();
    void createGui();
    void createCamera();
    void createViewports();


    void createSceneManager();
    void createScene();
    void destroyScene();

 private:
  Light* m_l;
  GameObject *m_ground;
  OgreOde::World *m_world;
  OgreOde::TriangleMeshGeometry *m_track;
  Real m_time_step;
  MyGUI::Gui * mGUI;

};


#endif
