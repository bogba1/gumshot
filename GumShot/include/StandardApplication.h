#ifndef __StandardApplication_H__
#define __StandardApplication_H__

#include "Ogre.h"
#include "OgreConfigFile.h"
#include "StandardFrameListener.h"
#include "Resource.h"

using namespace Ogre;

/** Base class which manages the standard startup of an Ogre application.
    Designed to be subclassed for specific examples if required.
*/
class StandardApplication
{
	public:
		StandardApplication();
		virtual ~StandardApplication();
	
	//Methods:
		virtual void				go(void);
	protected:  
		virtual bool				setup(void);
		virtual bool				configure(void);
		virtual void				chooseSceneManager(void);
		virtual void				createCamera(void);
		virtual void				createFrameListener(void);
		virtual void				createScene(void) = 0;
		virtual void				createLights(void) = 0;
		virtual void				destroyScene(void);
		virtual void				createViewports(void);
		virtual void				setupResources(void);
		virtual void				createResourceListener(void);
		virtual void				loadResources(void);

	//Attributes:
		Root*						_root;
		Camera*						_camera;
		SceneManager*				_sceneManager;
		StandardFrameListener*		_frameListener;
		RenderWindow*				_window;
		Ogre::String				_resourcePath;
};


#endif
