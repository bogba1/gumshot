#include "..\include\DataManager.h"

DataManager* DataManager::_instance = NULL;

DataManager::DataManager(void)
{
	_sceneMngr = NULL;
}

DataManager::~DataManager(void)
{
	//Erasing bodies in vector
	while(_bodies.size())
	{
		delete _bodies[0];
		_bodies.erase( _bodies.begin() );
	}
}

DataManager* DataManager::getInstance()
{
	if(_instance == NULL)
		_instance = new DataManager();
	return _instance;
}

std::vector<OgreNewt::Body*>& DataManager::getBodiesVec()
{
	return _bodies;
}

Ogre::SceneManager* DataManager::getSceneMngr()
{
	try
	{
		if(_sceneMngr == NULL)
			throw Ogre::Exception(1, "SceneManager has not been referenced yet in Datamanager!", "Datamanager.cpp");
		else
			return _sceneMngr;
	}
	catch(Ogre::Exception& e)
	{
		MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
}

void DataManager::setSceneMngr(Ogre::SceneManager *ref)
{
	_sceneMngr = ref;
}