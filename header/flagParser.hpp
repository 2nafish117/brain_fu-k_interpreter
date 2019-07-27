#pragma once

#include <iostream>
#include <cstring>

// #include "config.hpp"

/*
general command:

fuck [-f fileName] [-b size in bytes] [-p position] [-e number of errors]

Use cases:
fuck -f fileName			# interpret file fileName
fuck -f fileName -b 1024	# set buffer size to 1024 bytes
fuck -f fileName -p 10		# set data pointer to 10 before program starts
fuck -f fileName -e 100 	# show 100 errors
fuck -f fileName -n			# show numbers instead of charecters (space separarted numbers is output)
*/ 


class FlagParser
{
public:
	void parse(int argc, char* argv[]);
};

// @Todo: make sure user input is clean and prompts correctly when incorrect. 
void FlagParser::parse(int argc, char* argv[])
{
	for(int i = 1;i < argc;++i)
	{
		if(strcmp(argv[i], "-f") == 0)
		{
			if(i+1 < argc)
				Config::filePath = argv[i+1];
			else
			{
				std::cerr << "usage: fuck [-f fileName], no fileName specified\n";
				exit(EXIT_FAILURE);
			}
			i++;
		}
		else if(strcmp(argv[i], "-b") == 0)
		{
			if(i+1 < argc)
			{
				int err = sscanf(argv[i+1], "%u", &Config::bufferSizeInBytes);
				if(err != 1)
				{
					std::cerr << "usage: fuck [-b size], positive integer size in bytes\n";
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				std::cerr << "usage: fuck [-b size], no size specified\n";
				exit(EXIT_FAILURE);
			}
			i++;
		}
		else if(strcmp(argv[i], "-p") == 0)
		{
			if(i+1 < argc)
			{
				int err = sscanf(argv[i+1], "%u", &Config::initialDataPointerPosition);
				if(err < 0)
				{
					std::cerr << "usage: fuck [-p position], positive integer index\n";
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				std::cerr << "usage: fuck [-p position], no position specified\n";
				exit(EXIT_FAILURE);
			}
			i++;
		}
		else if(strcmp(argv[i], "-e") == 0)
		{
			if(i+1 < argc)
			{
				int err = sscanf(argv[i+1], "%u", &Config::maxNumErrorsShown);
				if(err != 1)
				{
					std::cerr << "usage: fuck [-e number], positive integer value\n";
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				std::cerr << "usage: fuck [-e number], no number specified\n";
				exit(EXIT_FAILURE);
			}
			i++;
		}
		else if(strcmp(argv[i], "-n") == 0)
		{
			Config::showNumInsteadOfChar = true;
		}
		else
		{
			std::cerr << "unknown flag: " << argv[i] << "\n";
			exit(EXIT_FAILURE);
		}
	}
}
