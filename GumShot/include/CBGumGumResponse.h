#pragma once
#include "OgreNewt.h"
#include "Ogre.h"

using namespace OgreNewt;
using namespace Ogre;

class CBGumGumResponse : public ContactCallback
{
	public:
		CBGumGumResponse(void);
		~CBGumGumResponse(void);

		void contactsProcess(ContactJoint& contactJoint, Real timeStep, int threadIndex);
};
