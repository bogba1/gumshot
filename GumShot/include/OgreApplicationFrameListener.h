#pragma once
#include "StandardFrameListener.h"

class OgreApplicationFrameListener : public StandardFrameListener
{
	public:
		OgreApplicationFrameListener(SceneManager* sceneManager, RenderWindow* window, Camera* cam);

		bool					frameStarted(const FrameEvent& evt);
		bool					frameEnded(const FrameEvent& evt);
		bool					processUnbufferedKeyInput(const FrameEvent& evt);
		bool					processUnbufferedMouseInput(const FrameEvent& evt);

	
	private:
	   SceneManager*			_sceneManager;
	   Camera*					_cam;
	   double					_timer;

};