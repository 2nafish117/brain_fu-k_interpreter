#pragma once

namespace Config
{
	// [fileName] default filename if no filename specified
	static std::string filePath("brain.fuck");
	// [-e] changes number of errors shown if any
	static unsigned int maxNumErrorsShown = 10;
	// [-b] changes amount of memory used in bytes
	static unsigned int bufferSizeInBytes = 1024;
	// [-p] changes the initial position if data pointer
	static unsigned int initialDataPointerPosition = 0;
	
}

