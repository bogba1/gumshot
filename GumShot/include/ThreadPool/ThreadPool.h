#pragma once
#include "IThreadable.h"
#include "SyncTools.h"
#include <vector>


typedef unsigned int uint;
	
class ThreadPool
{	
	public:
		ThreadPool(uint poolSize = 10);
		~ThreadPool(void);
	

		void						submitTask(IThreadable* threadable); //enques task for execution (worker will be deleted after execution)
	
	private:
		IThreadable*				getTask(); //waits for eventsignal, Locks queue, dequeues task, unlocks queue, returns task
		static unsigned int WINAPI	threads_main(void* param);


		Mutex						_queueLock;
		Semaphore					_tasksAvailable;
		std::vector<IThreadable*>	_taskQueue;
		std::vector<HANDLE>			_threadHandles;
};
