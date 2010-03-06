#include "..\include\CBGumResponsePnt.h"

CBGumResponsePnt::CBGumResponsePnt()
{
}

CBGumResponsePnt::~CBGumResponsePnt()
{
}

void CBGumResponsePnt::contactsProcess(OgreNewt::ContactJoint& contactJoint, Ogre::Real timeStep, int threadIndex)
{
	contactJoint.getBody0()->addImpulse(Vector3(0,100,0), Vector3(0,11,0));
}