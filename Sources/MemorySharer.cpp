#include <MemorySharer.h>

// STL includes
#include <iostream>

// Windows API
#include <Windows.h>

namespace SharedMemory
{
	MemorySharer::MemorySharer()
	{
		shmem_size = sizeof(*buf);

		mutex = CreateMutex(NULL, FALSE, L"mutex_name");

		shmem = CreateFileMapping(
			INVALID_HANDLE_VALUE,
			NULL,
			PAGE_READWRITE,
			0,
			shmem_size,
			L"shared_memory_name"
			);

		buf = static_cast<SHAREDBUFFER_t*> (MapViewOfFile(shmem, FILE_MAP_ALL_ACCESS, 0, 0, shmem_size));
	}

	MemorySharer::~MemorySharer()
	{
		// release
		UnmapViewOfFile(buf);
		CloseHandle(shmem);
		ReleaseMutex(mutex);
	}

	SHAREDBUFFER_t MemorySharer::read_shared_buffer() const
	{
		// mutex lock
		WaitForSingleObject(mutex, INFINITE);

		// Read in shared memory
		SHAREDBUFFER_t wValue = *buf;

		// mutex unlock
		ReleaseMutex(mutex);

		return wValue;
	}

	void MemorySharer::write_shared_buffer(SHAREDBUFFER_t iValue) const
	{
		// mutex lock
		WaitForSingleObject(mutex, INFINITE);

		// write in shared memory
		*buf = iValue;

		// mutex unlock
		ReleaseMutex(mutex);
	}
}