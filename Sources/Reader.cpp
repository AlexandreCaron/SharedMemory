#include "Reader.h"

#include <Windows.h>
#include <iostream>

namespace SharedMemory
{
	void Reader::execute()
	{
		for (uint32_t c = 0; c < 60; ++c) {
			// read shared memory
			uint32_t wValue = read_shared_buffer();

			// Log to console
			std::cout << "read shared memory...c=" << wValue << std::endl;

			Sleep(1000);
		}
	}
}