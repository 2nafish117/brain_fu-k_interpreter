#pragma once

namespace Config
{
	/*
	* forward declarations for configs, include everywhere!!
	*/

	// [fileName] default filename if no filename specified
	extern std::string filePath;
	// [-e] changes number of errors shown if any
	extern unsigned int maxNumErrorsShown;
	// [-b] changes amount of memory used in bytes
	extern unsigned int bufferSizeInBytes;
	// [-p] changes the initial position if data pointer
	extern unsigned int initialDataPointerPosition;
	// [-n] makes the output in (8 bit, space separated, signed) integers instead of ASCII charecters. 
	extern bool showNumInsteadOfChar;

	extern void showConfigSettings();
}


