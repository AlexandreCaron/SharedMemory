#include "Writer.h"

#include <Windows.h>
#include <iostream>

namespace SharedMemory
{
	void Writer::execute()
	{
		for (uint32_t c = 0; c < 60; ++c) {
			// write to shared memory
			write_shared_buffer(c);

			// Log to console
			std::cout << "write shared memory...c=" << c << std::endl;

			Sleep(1000);
		}
	}
}