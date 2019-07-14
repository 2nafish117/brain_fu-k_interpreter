#include <iostream>
#include <fstream>

#include "brainFuckVM.hpp"
#include "program.hpp"
#include "config.hpp"
#include "flagParser.hpp"

int main(int argc, char* argv[])
{
	FlagParser parser;
	parser.parse(argc, argv);

	std::cout << Config::filePath << "\n";
	std::cout << Config::bufferSizeInBytes << "\n";
	std::cout << Config::initialDataPointerPosition << "\n";
	std::cout << Config::maxNumErrorsShown << "\n";

	BrainFuckVM vm;
	Program prog(Config::filePath);
	vm.executeProgram(prog);
	std::cout.flush();
	
	return EXIT_SUCCESS;
}