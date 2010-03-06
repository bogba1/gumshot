#pragma once
#include "windows.h"

class Semaphore
{
	public:
		Semaphore(unsigned long initialCount = 0, unsigned long maxCount = 255)
		{
			// 2 start 
			// 3 auto reset after every Wait
			_handle = CreateSemaphore(0, initialCount, maxCount, NULL);
		}

		~Semaphore()
		{
			CloseHandle(_handle);
		}

		// increment the counter by the given value possibly signalling pending waits
		unsigned long signal(unsigned long increment = 1) {
			long previousCount;
			ReleaseSemaphore(_handle, increment, &previousCount);
			return (unsigned long)previousCount;
		}

		void wait()
		{	
			// Wait until the counter is at least one and decrement the counter afterwards by one
			WaitForSingleObject(_handle, INFINITE);
		}
		operator HANDLE () { return _handle; }

	private:
		HANDLE _handle;
};
