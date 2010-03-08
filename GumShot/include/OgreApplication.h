#pragma once

#include "StandardApplication.h"
#include "OgreApplicationFrameListener.h"
#include <OgreNewt.h>
#include "GS_Callbacks.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

using namespace OgreNewt;

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
		void					setupGumMachine(const Vector3& position, const String& parentNode);
		void					setupPlotter(const Vector3& position, const String& parentNode);
		void					setupBubbleGums(const int size, const int quantity, const Vector3& offset, const String& machineNode);
		void					createMaterialPair(MaterialID* mat1, MaterialID* mat2, ContactCallback* callback, float softness,
												   float elasticity, float frictionStatic, float frictionKinetic);

	private:
		World*					_world;
		BasicFrameListener*		_physicFrameListener;
		MaterialID*				_matResponsePoint;
		MaterialID*				_matInnerBarricade;
		MaterialID*				_matGums;
		CBGumResponsePnt		_gumBarricadeResp;
		CBGumGumResponse		_gumGumResp;

};
