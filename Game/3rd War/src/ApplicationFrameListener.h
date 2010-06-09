#ifndef _ApplicationFrameListener_
#define _ApplicationFrameListener_

#define OIS_DYNAMIC_LIB

#include <Ogre.h>
#include <OgreStringConverter.h>
#include <OgreException.h>
#include <OgreOde_Core.h>
#include <OgreOde_Loader.h>
#include <OgreOde_Prefab.h>

#include <OIS/OIS.h>

using namespace Ogre;
using namespace OgreOde;
using namespace OgreOde_Prefab;
using namespace OgreOde_Loader;


class ApplicationFrameListener: public FrameListener, public WindowEventListener
{
public:
	// Constructor takes a RenderWindow because it uses that to determine input context
	ApplicationFrameListener(RenderWindow* win, Camera* cam, bool bufferedJoy = false );

	//Unattach OIS before window shutdown (very important under Linux)
	virtual void windowClosed(RenderWindow* rw);

	virtual ~ApplicationFrameListener();

	virtual bool processUnbufferedKeyInput(const FrameEvent& evt) = 0;

    bool frameStarted(const FrameEvent &evt);
	// Override frameRenderingQueued event to process that (don't care about frameEnded)
	bool frameRenderingQueued(const FrameEvent& evt);

	bool frameEnded(const FrameEvent& evt);

    void windowResized(Ogre::RenderWindow* rw);

protected:
	Camera* mCamera;

	Real mCurrentSpeed;
	RenderWindow* mWindow;

	unsigned int mNumScreenShots;

	// just to stop toggles flipping too fast
	Real mTimeUntilNextToggle ;
	TextureFilterOptions mFiltering;
	int mAniso;

	int mSceneDetailIndex ;


	//OIS Input devices
	OIS::InputManager* mInputManager;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;
};
#endif
