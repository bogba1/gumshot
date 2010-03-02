#include "OgreApplicationFrameListener.h"

OgreApplicationFrameListener::OgreApplicationFrameListener(SceneManager* sceneManager, RenderWindow* window, Camera *cam)
: StandardFrameListener(window, cam)
{
	_sceneManager = sceneManager;
	this->_cam = cam;
	_timer = NULL;
}

//------------------------------------------------------

bool OgreApplicationFrameListener::frameStarted(const FrameEvent& evt)
{
	_timer += evt.timeSinceLastFrame;
	double _dt = evt.timeSinceLastFrame;

	//rotating cube dings
	Node* _node = _sceneManager->getRootSceneNode()->getChild("gs_ball_machine_node");
	Vector3 _vec = Vector3(.2+sin(_timer), cos(_timer), .4+sin(_timer));
	//_node->rotate(_vec,Radian(45*(Math::PI/180)) * _dt);


	//does not work with 1.7 SDK
	//StandardFrameListener::updateStats();
	return true;
}

//------------------------------------------------------

bool OgreApplicationFrameListener::frameEnded(const FrameEvent& evt)
{

	return true;	
}

//------------------------------------------------------

bool OgreApplicationFrameListener::processUnbufferedKeyInput(const Ogre::FrameEvent &evt)
{
	return StandardFrameListener::processUnbufferedKeyInput(evt);
}

bool OgreApplicationFrameListener::processUnbufferedMouseInput(const FrameEvent& evt)
{
	return StandardFrameListener::processUnbufferedMouseInput(evt);
}