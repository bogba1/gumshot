#pragma once
#include "windows.h"

class Mutex
{
	public:

		Mutex(void)
		{
			_mHandle = CreateMutex(NULL, false, NULL);
		}

		~Mutex(void)
		{
			CloseHandle( _mHandle );
		}

		void lock()
		{
			WaitForSingleObject( _mHandle, INFINITE);
		}

		void unlock()
		{
			ReleaseMutex( _mHandle );
		}

	private:
		HANDLE _mHandle;
};
