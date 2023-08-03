#include "Reader.h"
#include "Writer.h"

#include <string>
#include <iostream>

int main(int argc, char* argv[])
{	
	std::string wInput;
	SharedMemory::MemorySharer* wProcess = nullptr;

	// Input validation
	if (argc < 2)
	{
		std::cerr << "Expected cmd line argument : either reader or writer" << std::endl;
		return -1;
	}
	else
	{
		wInput = argv[1];
	}

	// Based on input, set Process to the associated type
	if (wInput == "reader")
	{
		wProcess = new SharedMemory::Reader;
	}
	else if (wInput == "writer")
	{
		wProcess = new SharedMemory::Writer;
	}
	else
	{
		std::cerr << "Expected cmd line argument : either reader or writer" << std::endl;
		return -1;
	}

	// Run the process
	wProcess->execute();

	// Clean-up
	delete wProcess;
	wProcess = nullptr;
	
	return 0;
}