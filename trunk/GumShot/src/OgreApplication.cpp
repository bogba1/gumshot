#include "OgreApplication.h"
#include "DataManager.h"


OgreApplication::OgreApplication() 
: StandardApplication()
{
	_world = new World();
	_matGums = new MaterialID(_world);
	_matInnerBarricade = new MaterialID(_world);
	_matResponsePoint = new MaterialID(_world);
}

//------------------------------------------------------

OgreApplication::~OgreApplication()
{
	delete _world;
	delete _matGums;
	delete _matInnerBarricade;
	delete _matResponsePoint;
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
	if(!StandardApplication::configure())
		return false;
	else{
		DataManager::getInstance()->setSceneMngr(_sceneManager);
		return true;
	}
}

//------------------------------------------------------

void OgreApplication::createScene()
{
	_sceneManager->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
	_sceneManager->setShadowFarDistance(1000);
	setupGumMachines();
	setupBubbleGums( 1, 10, Vector3(0, 18, 0 ), "gs_gummachine_1" );


/*
	Ogre::MovablePlane* _plane = new Ogre::MovablePlane("Plane");
	_plane->d = 0;
	_plane->normal = Vector3::UNIT_Y;
		Ogre::MeshManager::getSingleton().createPlane("planeMesh",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	*_plane, 80, 80, 20, 20, true, 1, 3, 3, Vector3::UNIT_Z);
	Entity *_planeEnt = _sceneManager->createEntity("plane", "planeMesh");
	_planeEnt->setCastShadows(false);
	_planeEnt->setMaterialName("plane_mat");
	_node = _sceneManager->getRootSceneNode()->createChildSceneNode("planeNode");
	_node->attachObject(_planeEnt);
	_node->setPosition(0,0,0);
*/
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

void OgreApplication::setupGumMachines()
{
	//Gummachine 1
	//visible part of the gummachine
	Entity* _entity = _sceneManager->createEntity( "gs_sockel_glas", "gs_sockel_glas.mesh" );
	_entity->setCastShadows( true );
	SceneNode* _node = _sceneManager->getRootSceneNode()->createChildSceneNode( "gs_gummachine_1" );
	_node->attachObject( _entity );


	//inner transparent barricade (bounce of the gums)
	_entity = _sceneManager->createEntity("gs_inner_barricade", "gs_inner_barricade.mesh");
	_entity->setCastShadows( false );
	SceneNode* _childNode = _node->createChildSceneNode( "inner_barricade" ); //no creation over _scenemangager due to adding this as child of node "gs_gummachine_1"
	_childNode->attachObject( _entity );

	//collisionshape of the barricade
	CollisionPrimitives::TreeCollisionSceneParser* _colShape = new CollisionPrimitives::TreeCollisionSceneParser( _world );
	_colShape->parseScene( _childNode, 1 );
	OgreNewt::Body* _body = new OgreNewt::Body(_world, (CollisionPtr) _colShape); 
	_body->setPositionOrientation(Ogre::Vector3(0, 0, 0), Ogre::Quaternion::IDENTITY);
	_body->attachNode( _childNode );
	_body->setMaterialGroupID( _matInnerBarricade ); //matgroupID for collresponse

	//response point
	_entity = _sceneManager->createEntity("gs_response_point", "gs_response_point.mesh");
	_entity->setCastShadows( false );
	_childNode = _node->createChildSceneNode( "gs_response_point" );
	_childNode->attachObject( _entity );

	_colShape = new CollisionPrimitives::TreeCollisionSceneParser( _world );
	_colShape->parseScene( _childNode, 2 );
	_body = new OgreNewt::Body( _world, (CollisionPtr) _colShape ); 
	_body->setPositionOrientation(Ogre::Vector3(0, 0, 0), Ogre::Quaternion::IDENTITY);
	_body->attachNode( _childNode );
	_body->setMaterialGroupID( _matResponsePoint ); //matgroupID for colliresponse
}

void OgreApplication::setupBubbleGums(const int size, const int quantity, const Vector3& offset, const Ogre::String machineNode)
{
	float _angleStep = (2.0f * Ogre::Math::PI) / quantity;
	int _namingNmbr = 0;

	for(int i=0; i < quantity; i++)
	{
		for(int u=0; u < quantity; u++)
		{
			std::ostringstream oss;
			oss << "gs_gum_" << ( _namingNmbr );
			int _sSz = 10; //size of the transparent collsphere
			
			// _angleStep * i = phi
			// _angleStep * u = theta

			Vector3 _accPos( _sSz * (cos( _angleStep * i ) * cos( _angleStep * u )), //X
							  _sSz * (sin( _angleStep * i ) * cos( _angleStep * u )), //Y
							  _sSz * (sin( _angleStep * u ))					      //Z
							 );

			//creating entity + node
			Entity* _entity = _sceneManager->createEntity( oss.str(), "gs_gum.mesh" );
			_entity->setCastShadows( true );
			SceneNode* _node = _sceneManager->getSceneNode( "gs_gummachine_1" )->createChildSceneNode( oss.str() + "_node" );
			_node->attachObject( _entity );
			
			//creating collsphape, body
			ConvexCollisionPtr _colShape = ConvexCollisionPtr( new CollisionPrimitives::Ellipsoid( _world, Vector3(size, size, size),_namingNmbr ) );
			OgreNewt::Body* _body = new OgreNewt::Body( _world, _colShape );
			_body->attachNode( _node );
			_body->setPositionOrientation(_accPos + offset, Ogre::Quaternion::IDENTITY);
			
			//setting mass, center of mass, materialID
			Vector3 _inertia, _offset;
			_colShape->calculateInertialMatrix( _inertia, _offset );
			_body->setMassMatrix( 10, (10 * _inertia) );
			_body->setCenterOfMass( _offset );
			_body->setMaterialGroupID( _matGums );
			DataManager::getInstance()->getBodiesVec().push_back( _body );
			++_namingNmbr;
		}
	}
	
}

void OgreApplication::createMaterialPair(MaterialID* mat1, MaterialID* mat2, ContactCallback* callback, float softness,
										 float elasticity, float frictionStatic, float frictionKinetic)

{
	OgreNewt::MaterialPair* _matPair = new OgreNewt::MaterialPair( _world, mat1, mat2 );
	_matPair->setContactCallback( callback ); //setting contact object (called on collision)
	//setting attitudes
	_matPair->setDefaultSoftness( softness );
    _matPair->setDefaultElasticity( elasticity );
    _matPair->setDefaultFriction( frictionStatic, frictionKinetic );

}