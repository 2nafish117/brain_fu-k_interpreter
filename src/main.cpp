#include <iostream>
#include <fstream>

#include "config.hpp"
#include "brainFuckVM.hpp"
#include "program.hpp"
#include "flagParser.hpp"

int main(int argc, char* argv[])
{
	FlagParser parser;
	parser.parse(argc, argv);
	// Config::showConfigSettings();

	BrainFuckVM vm; 
	Program prog(Config::filePath);
	vm.executeProgram(prog);
	std::cout.flush();
	
	return EXIT_SUCCESS;
}