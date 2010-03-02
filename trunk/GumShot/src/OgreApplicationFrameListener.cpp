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
	Node* _node = _sceneManager->getRootSceneNode()->getChild("cubeDingNode");
	Vector3 _vec = Vector3(.2+sin(_timer), cos(_timer), .4+sin(_timer));
	_node->rotate(_vec,Radian(45*(Math::PI/180)) * _dt);

	//rotating cube
	_node = _sceneManager->getRootSceneNode()->getChild("cubeNode");
	_node->roll(Radian(9*(Math::PI/180)) * _dt); //rotating 9°/sec z-axis
	_node->pitch(Radian(4.5*(Math::PI/180)) * _dt); //rotating 4,5°/sec x-axis
	_node->yaw(Radian(18*(Math::PI/180)) * _dt); //rotating 18°/sec y-axis

	//rotate pLight around cube
	_node = _sceneManager->getRootSceneNode()->getChild("pLightNode");
	_node->rotate(Vector3(0,1,0), Radian(180*(Math::PI/180))* _dt);
	_vec = _node->getPosition();
	_node->setPosition(_vec * Vector3(0,sin(_timer),0));

	//does not work with 1.7 SDK
	//StandardFrameListener::updateStats();
	return true;
}

//------------------------------------------------------

bool OgreApplicationFrameListener::frameEnded(const FrameEvent& evt)
{
	//setting light to camera position and direction to center
	Light* _light = _sceneManager->getLight("light2");
	Vector3 _vec = Vector3(_cam->getPosition().x, _cam->getPosition().y, _cam->getPosition().z);
	_light->setPosition(_vec);
	_light->setDirection(Vector3(0,0,0) - _vec);
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