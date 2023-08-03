#pragma once

#include <MemorySharer.h>

namespace SharedMemory
{
	class Writer : public MemorySharer
	{
	public:
		virtual void execute();
	};
}