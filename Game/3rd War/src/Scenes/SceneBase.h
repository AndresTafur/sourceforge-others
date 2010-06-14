#ifndef _SCENE_BASE_H
#define _SCENE_BASE_H

#include <Ogre.h>
#include "../ApplicationFrameListener.h"
#include "../GameObject.h"


/**
 * @interface
 * Interface within commond scenes behaviour methods.
 */
class SceneBase : public FrameListener
{
public:

    /**
     * Creates Frame listener. Called first, when the framelistener has to be built.
     * @see Application.
     */
    virtual void createFrameListener() = 0;

    /**
     * Creates Mygui. Called when the gui has to be built.
     * @see Application.
     */
    virtual void createGui() = 0;

    /**
     * Creates the camera.
     * @see Application.
     */
    virtual void createCamera() = 0;

    /**
     * Creates every viewport.
     * @see Application.
     */
    virtual void createViewports() = 0;

    /**
     * Creates the scene manager for this scene.
     * @see Application.
     */
    virtual void createSceneManager() = 0;

    /**
     * Creates the scene including mesh loading, lighting and physics.
     * @see Application.
     */
    virtual void createScene() = 0;


    /**
     * Releases everything used.
     * @see Application.
     */
    virtual void destroyScene() = 0;

protected:
/**
 * Frame listener to be assigned.
 */
ApplicationFrameListener* mFrameListener;

/**
 * Frame listener to be assigned.
 */
RenderWindow* mWindow;

/**
 * SceneManager of the scene.
 */
SceneManager* mSceneMgr;

/**
 * Current camera.
 */
Camera* mCamera;

/**
 * Scene Meshes.
 */
 std::vector<GameObject*> m_meshes;
};
#endif
