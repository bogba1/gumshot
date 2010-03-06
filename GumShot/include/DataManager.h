#pragma once
#include <Ogre.h>
#include <OgreNewt.h>

class DataManager
{
	private:
		DataManager(void);
		~DataManager(void);
		DataManager(const DataManager& dm);

		static DataManager*					_instance;
		std::vector<OgreNewt::Body*>		_bodies;
		Ogre::SceneManager*					_sceneMngr;

	public:
		static DataManager*					getInstance(); //returns singletons instance
		std::vector<OgreNewt::Body*>&	getBodiesVec(); //returns reference to bodies vector
		Ogre::SceneManager*					getSceneMngr(); //returns reference to sceneManager
		void								setSceneMngr(Ogre::SceneManager* ref);

};
