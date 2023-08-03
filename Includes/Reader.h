#pragma once

#include <MemorySharer.h>

namespace SharedMemory
{
	class Reader : public MemorySharer
	{
	public:
		virtual void execute();
	};
}