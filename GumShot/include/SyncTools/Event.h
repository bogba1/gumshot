#pragma once
#include "windows.h"

class Event
{
	public:
		Event ()
		{
			// 2 start in non-signaled state
			// 3 auto reset after every Wait
			_handle = CreateEvent(0, FALSE, FALSE, 0);
		}

		~Event ()
		{
			CloseHandle(_handle);
		}

		void setSignal() { SetEvent(_handle); }
		void wait()
		{	
			// Wait until event is in signaled state
			WaitForSingleObject(_handle, INFINITE);
		}
		operator HANDLE () { return _handle; }

	private:
		HANDLE _handle;
};
