#ifndef _SCENE_BASE_H
#define _SCENE_BASE_H

#include <Ogre.h>
#include "../ApplicationFrameListener.h"


class SceneBase
{
public:

    virtual void createFrameListener() = 0;

    virtual void createGui() = 0;

    virtual void createCamera() = 0;

    virtual void createViewports() = 0;


    virtual void createSceneManager() = 0;

    virtual void createScene() = 0;

    virtual void destroyScene() = 0;

protected:
ApplicationFrameListener* mFrameListener;
RenderWindow* mWindow;
SceneManager* mSceneMgr;
Camera* mCamera;

};
#endif
