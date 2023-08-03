#pragma once

// Standard library includes
#include <cstdint>

// Remove header dependency on Windows.h
typedef void* HANDLE;
typedef unsigned long DWORD;

// Type of the shared buffer
typedef uint32_t SHAREDBUFFER_t;

namespace SharedMemory
{
  class MemorySharer
  {
  public:
    MemorySharer();
    ~MemorySharer();

    virtual void execute() = 0;

  protected:
    SHAREDBUFFER_t read_shared_buffer() const;
    void write_shared_buffer(SHAREDBUFFER_t iValue) const;

  private:
    DWORD shmem_size;
    HANDLE shmem;
    HANDLE mutex;
    SHAREDBUFFER_t* buf;
  };
}