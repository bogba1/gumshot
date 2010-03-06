#pragma once
#include "OgreNewt.h"
#include "Ogre.h"

using namespace OgreNewt;
using namespace Ogre;

class CBGumResponsePnt : public ContactCallback
{
	public:
		CBGumResponsePnt();
		~CBGumResponsePnt();

		void contactsProcess(ContactJoint& contactJoint, Real timeStep, int threadIndex);
};
