#pragma once

#include "StandardApplication.h"
#include "OgreApplicationFrameListener.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

class OgreApplication : public StandardApplication
{
	public:
		OgreApplication();
		~OgreApplication();

	protected:

		void					createCamera(void);
		bool					configure(void);
		void					createScene(void);
		void					createFrameListener(void);
		void					createLights(void);
};
