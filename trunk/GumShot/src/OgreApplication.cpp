#include "OgreApplication.h"

using namespace OgreNewt;

OgreApplication::OgreApplication() 
: StandardApplication()
{
	_world = new World();
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
	Entity* _entity = _sceneManager->createEntity("gs_ball_machine", "gs_ball_machine.mesh");
	_entity->setCastShadows(true);
	SceneNode* _node = _sceneManager->getRootSceneNode()->createChildSceneNode("gs_ball_machine_node"); //_sceneManager->createSceneNode("nodeHallo");
	_node->attachObject(_entity);
	_node->setPosition(0,0,0);


	CollisionPrimitives::TreeCollisionSceneParser* _colShape = new CollisionPrimitives::TreeCollisionSceneParser(_world);
	_colShape->parseScene(_node,1);
	OgreNewt::Body* _body = new OgreNewt::Body(_world, CollisionPtr(_colShape)); //creating rigidBody -> has mass, size, and shape; interacts with other rigidBodys WHY DO NOT DEREFERENCING _levelColShape for CollisionPtr& col ?!?! -> reference! 
	_body->attachNode(_node); //attaching level node to rigidbody(collision shaped)
	_body->setPositionOrientation(Ogre::Vector3(0, 0, 0), Ogre::Quaternion::IDENTITY);

	_entity = _sceneManager->createEntity("gs_cube", "cube.mesh");
	_entity->setCastShadows(true);
	_node = _sceneManager->getRootSceneNode()->createChildSceneNode("gs_cube"); //_sceneManager->createSceneNode("nodeHallo");
	_node->attachObject(_entity);
	_node->setScale(0.01,0.01,0.01);
	_node->setPosition(0,0,0);

	ConvexCollisionPtr _colShapeBox = ConvexCollisionPtr(new CollisionPrimitives::Box(_world,Vector3(1,1,1),1));
	_body = new OgreNewt::Body(_world, _colShapeBox); //creating rigidBody -> has mass, size, and shape; interacts with other rigidBodys WHY DO NOT DEREFERENCING _levelColShape for CollisionPtr& col ?!?! -> reference! 
	Vector3 _inertia, _offset;
	_colShapeBox->calculateInertialMatrix(_inertia, _offset);
	_body->setMassMatrix(10, (10 * _inertia));
	_body->setCenterOfMass(_offset);
	_body->attachNode(_node); //attaching level node to rigidbody(collision shaped)
	_body->setPositionOrientation(Ogre::Vector3(4, 9, 0), Ogre::Quaternion::IDENTITY);
	_body->setStandardForceCallback();
	

	Ogre::MovablePlane* _plane = new Ogre::MovablePlane("Plane");
	_plane->d = 0;
	_plane->normal = Vector3::UNIT_Y;
		Ogre::MeshManager::getSingleton().createPlane("planeMesh",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	*_plane, 80, 80, 20, 20, true, 1, 3, 3, Vector3::UNIT_Z);
	Entity *_planeEnt = _sceneManager->createEntity("plane", "planeMesh");
	_planeEnt->setCastShadows(true);
	_planeEnt->setMaterialName("planeMat");
	_node = _sceneManager->getRootSceneNode()->createChildSceneNode("planeNode");
	_node->attachObject(_planeEnt);
	_node->setPosition(0,0,0);
}

//------------------------------------------------------

void OgreApplication::createFrameListener()
{
	_frameListener = new OgreApplicationFrameListener(_sceneManager, _window, _camera);
	_physicFrameListener = new OgreNewt::BasicFrameListener(_window, _world);

	_root->addFrameListener(_frameListener);
	_root->addFrameListener(_physicFrameListener);
}

//------------------------------------------------------

void OgreApplication::createLights()
{
	_sceneManager->setAmbientLight(Ogre::ColourValue(0.3,0.3,0.3));

	//directional yellow light
	Light* _light = _sceneManager->createLight("light1");
	_light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
	_light->setDiffuseColour(ColourValue(1, 1, 1));
    _light->setSpecularColour(ColourValue(1, 1, 1));
	_light->setDirection(0,-1,1);
	_light->setCastShadows(true);


	SceneNode* _node = _sceneManager->getRootSceneNode()->createChildSceneNode("pLightNode");
	_node->attachObject(_light);
	_node->setPosition(0,0,0);

}
