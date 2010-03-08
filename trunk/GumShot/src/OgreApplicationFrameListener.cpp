#include "OgreApplicationFrameListener.h"
#include "DataManager.h"

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
	//Node* _node = _sceneManager->getRootSceneNode()->getChild("gs_ball_machine_node");
	//Vector3 _vec = Vector3(.2+sin(_timer), cos(_timer), .4+sin(_timer));
	//_node->rotate(_vec,Radian(45*(Math::PI/180)) * _dt);


	//does not work with 1.7 SDK
	StandardFrameListener::updateStats();
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
	//enable gravity
	if(mKeyboard->isKeyDown( OIS::KC_G ))
	{
		std::vector<OgreNewt::Body*>& _bodies = DataManager::getInstance()->getBodiesVec();
		for(int i=0; i <_bodies.size(); i++)
		{
			_bodies[i]->setStandardForceCallback();
		}
	}

	//plotter turn-action
	if( mKeyboard->isKeyDown( OIS::KC_T ))
	{
		std::vector<OgreNewt::Body*>& _bodies = DataManager::getInstance()->getBodiesVec();
		for(int i=0; i<_bodies.size(); i++)
		{
			_bodies[i]->addImpulse( Vector3(2, -1, 4), Vector3(0,0,0) );
		}
		Ogre::Radian _angle = (Radian)Math::DegreesToRadians( 90 ) * evt.timeSinceLastFrame;
		_sceneManager->getSceneNode( "gs_plotter_turnthing")->roll( _angle );
	}

	return StandardFrameListener::processUnbufferedKeyInput(evt);
}

bool OgreApplicationFrameListener::processUnbufferedMouseInput(const FrameEvent& evt)
{
	const OIS::MouseState &ms=mMouse->getMouseState();
	if(ms.buttonDown(OIS::MB_Left)){
		Ogre::RaySceneQuery* _rayQuery=_sceneManager->createRayQuery(Ray());
		Ogre::Real _offsetX=ms.X.abs/ms.width;
		Ogre::Real _offsetY=ms.Y.abs/ms.height;
		Ogre::Ray _ray=_cam->getCameraToViewportRay(_offsetX, _offsetY);
		_rayQuery->setRay(_ray);
		_rayQuery->setSortByDistance(true);
		//_rayQuery->setQueryMask(~100);

		RaySceneQueryResult& _rayResult=_rayQuery->execute();
		// der erste
		RaySceneQueryResult::iterator i=_rayResult.begin();
		if(!_rayResult.empty()){
			bool find=false;
			while(!find && i!=_rayResult.end()){
				if(i->movable){
					Ogre::String name=i->movable->getParentSceneNode()->getName();
					if(name!="gs_gummachine_1" && name!="inner_barricade"){
						i->movable->getParentSceneNode()->showBoundingBox(true);
						find=true;
					}else
						i++;
				}
			}
		}
		// alle treffer
		/*for(RaySceneQueryResult::iterator i=_rayResult.begin(); i!=_rayResult.end(); i++){
			if(i->movable){
				i->movable->getParentSceneNode()->showBoundingBox(true);
			}
		}*/
	}
	return StandardFrameListener::processUnbufferedMouseInput(evt);
}