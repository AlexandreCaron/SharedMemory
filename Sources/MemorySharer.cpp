#include <MemorySharer.h>

// STL includes
#include <iostream>

// Windows API
#include <Windows.h>

namespace SharedMemory
{
  MemorySharer::MemorySharer()
  {
    mSharedMemorySize = sizeof(*mBuffer);

    mMutex = CreateMutex(NULL, FALSE, L"mutex_name");

    mSharedMemory = CreateFileMapping(
      INVALID_HANDLE_VALUE,
      NULL,
      PAGE_READWRITE,
      0,
      mSharedMemorySize,
      L"shared_memory_name"
    );

    mBuffer = static_cast<SHAREDBUFFER_t*> (MapViewOfFile(mSharedMemory, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemorySize));
  }

  MemorySharer::~MemorySharer()
  {
    // release
    UnmapViewOfFile(mBuffer);
    CloseHandle(mSharedMemory);
    ReleaseMutex(mMutex);
  }

  SHAREDBUFFER_t MemorySharer::read_shared_buffer() const
  {
    // mutex lock
    WaitForSingleObject(mMutex, INFINITE);

    // Read in shared memory
    SHAREDBUFFER_t wValue = *mBuffer;

    // mutex unlock
    ReleaseMutex(mMutex);

    return wValue;
  }

  void MemorySharer::write_shared_buffer(SHAREDBUFFER_t iValue) const
  {
    // mutex lock
    WaitForSingleObject(mMutex, INFINITE);

    // write in shared memory
    *mBuffer = iValue;

    // mutex unlock
    ReleaseMutex(mMutex);
  }
}