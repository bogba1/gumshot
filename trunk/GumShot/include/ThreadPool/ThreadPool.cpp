#include "ThreadPool.h"

unsigned int WINAPI ThreadPool::threads_main(void* param) {
	
	ThreadPool* _threadPool = (ThreadPool*)param;
	while(true)
	{
		IThreadable* _task = _threadPool->getTask();
		if(_task == NULL) continue;
		_task->run();
		delete _task;
	}
	return 0;
}

//-----------------------------------------------------------------

ThreadPool::ThreadPool(uint poolSize)
{
	uint _addr;
	unsigned long _size;
	if(poolSize == 0)_size = 10;
	else _size = poolSize;
	HANDLE *_handles = new HANDLE[_size];
	for(uint i=0; i<_size; i++)
	{
		_handles[i] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ThreadPool::threads_main, this, 0, (LPDWORD)&_addr);
		_threadHandles.push_back(_handles[i]);
	}
}

ThreadPool::~ThreadPool(void)
{
	uint _size = _taskQueue.size();
	for(uint i=0; i<_size; i++)
		delete _taskQueue[i];
	_taskQueue.empty();
}

void ThreadPool::submitTask(IThreadable* threadable)
{
	_queueLock.lock();
	_taskQueue.push_back(threadable);
	_queueLock.unlock();
	_tasksAvailable.signal();
}

IThreadable* ThreadPool::getTask()
{
	_tasksAvailable.wait();
	_queueLock.lock();
	IThreadable* _tmp = NULL;
	int size = 0;
	size = _taskQueue.size();
	if(_taskQueue.size() > 0)
	{
		_tmp = _taskQueue[0];
		_taskQueue.erase( _taskQueue.begin() );
	}
	_queueLock.unlock();
	return _tmp;
}
