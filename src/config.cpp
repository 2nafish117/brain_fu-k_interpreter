#include <iostream>

namespace Config
{
	// [fileName] default filename if no filename specified
	std::string filePath("brain.fuck");
	// [-e] changes number of errors shown if any
	unsigned int maxNumErrorsShown = 10;
	// [-b] changes amount of memory used in bytes
	unsigned int bufferSizeInBytes = 1024;
	// [-p] changes the initial position if data pointer
	unsigned int initialDataPointerPosition = 0;
	// [-n] makes the output in (8 bit, space separated, signed) integers instead of ASCII charecters. 
	bool showNumInsteadOfChar = false;

	extern void showConfigSettings()
	{
		std::cout << "===Config settings:===\n";
		std::cout << "file: 		" << Config::filePath << "\n";
		std::cout << "buffsize: 	" << Config::bufferSizeInBytes << "\n";
		std::cout << "initialpos: 	" << Config::initialDataPointerPosition << "\n";
		std::cout << "numerrors: 	" << Config::maxNumErrorsShown << "\n";
		std::cout << "shownum: 		" << Config::showNumInsteadOfChar << "\n";
	}
}
