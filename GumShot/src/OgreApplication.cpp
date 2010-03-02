#include "OgreApplication.h"

OgreApplication::OgreApplication() 
: StandardApplication()
{

}

//------------------------------------------------------

OgreApplication::~OgreApplication()
{

}

//------------------------------------------------------

void OgreApplication::createCamera()
{
	// Create the camera
	_camera = _sceneManager->createCamera("cam");
	_camera->setPosition(Vector3(0,10,30));
	_camera->lookAt(0,0,0);
	// Look back along -Z
	_camera->setNearClipDistance(0.1);
}

//------------------------------------------------------

bool OgreApplication::configure()
{
	return StandardApplication::configure();
}

//------------------------------------------------------

void OgreApplication::createScene()
{
	//here you can create entities, lights and other stuff
	_sceneManager->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
	_sceneManager->setShadowFarDistance(1000);
	Entity* _entity = _sceneManager->createEntity("cube_ding", "cube.mesh");
	_entity->setCastShadows(true);
	SceneNode* _node = _sceneManager->getRootSceneNode()->createChildSceneNode("cubeDingNode"); //_sceneManager->createSceneNode("nodeHallo");
	_node->attachObject(_entity);
	_node->setPosition(0,0,0);

	_entity = _sceneManager->createEntity("cube", "cube.mesh");
	_entity->setCastShadows(false);
	_node = _sceneManager->getRootSceneNode()->createChildSceneNode("cubeNode");
	_node->attachObject(_entity);
	_node->setPosition(0,0,0);
}

//------------------------------------------------------

void OgreApplication::createFrameListener()
{
	_frameListener = new OgreApplicationFrameListener(_sceneManager, _window, _camera);
	_root->addFrameListener(_frameListener);
}

//------------------------------------------------------

void OgreApplication::createLights()
{
	_sceneManager->setAmbientLight(Ogre::ColourValue(0.3,0.3,0.3));

	//directional yellow light
	Light* _light = _sceneManager->createLight("light1");
	_light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
	_light->setDiffuseColour(ColourValue(.25, .25, 0));
    _light->setSpecularColour(ColourValue(.25, .25, 0));
	_light->setDirection(0,-1,1);
	_light->setCastShadows(true);

	//light clamped to camera
	_light = _sceneManager->createLight("light2");
	_light->setType(Ogre::Light::LightTypes::LT_SPOTLIGHT);
	_light->setPosition(0,0,30);
	_light->setDiffuseColour(1,1,1);
	_light->setSpecularColour(.8,1,.8);
	_light->setAttenuation(100,1,0.005,0);
	_light->setSpotlightRange(Degree(35), Degree(50));
	_light->setCastShadows(true);

	//light rotating around cube
	_light = _sceneManager->createLight("light3");
	_light->setType(Light::LightTypes::LT_POINT);
	_light->setPosition(5,1,0);
	_light->setDiffuseColour(.5,.5,.5);
	_light->setSpecularColour(.3,.5,1);
	_light->setAttenuation(2,1,0,0);
	_light->setCastShadows(true);

	SceneNode* _node = _sceneManager->getRootSceneNode()->createChildSceneNode("pLightNode");
	_node->attachObject(_light);
	_node->setPosition(0,0,0);


}
