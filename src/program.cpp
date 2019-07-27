#include "program.hpp"
#include "config.hpp"

Program::Program(const std::string& path)
: mFilePath(path), mNumLines(1), mNumErrors(0)
{
	mFile.open(path);
	if(! mFile.is_open())
	{
		std::cerr << "[ERROR] " << path + " doesn't exist" << std::endl;
		exit(EXIT_FAILURE);
	}

	// std::cout << "tokenizing...\n";
	mTokenize();
	mHandleErrors();
}

Program::~Program()
{
	if(mFile.is_open())
		mFile.close();
}

std::string Program::getFilePath() const
{
	return mFilePath;
}

char Program::getToken(unsigned int instrPtr) const
{
	assert(instrPtr < mProgTokens.size());
	return mProgTokens[instrPtr];
}

unsigned int Program::getNumTokens() const
{
	return mProgTokens.size();
}

bool Program::mIsValidToken(char c) const
{
	static const char* tokens = "><+-.,[]";
	static const int numTokens = 8;

	for(int i = 0;i < numTokens;++i)
	{
		if(c == tokens[i])
			return true;
	}
	return false;
}

bool Program::mIsSpace(char c) const
{
	static const char* spaces = " \n\t";
	static const int numSpaceChars = 3;
	for(int i = 0;i < numSpaceChars;++i)
		if(c == spaces[i])
			return true;
	return false;
}

bool Program::mIsCommentLine(char c)
{
	if(c != '#')
		return false;

	char _;
	while(mFile.get(_))
	{
		/* skip untill a \n or eof */
		if(_ == '\n')
		{
			mNumLines++;
			break;
		}
	}
	return true;
}

// @Incomplete: how to handle jumps ?
// **method1: stack (do this)
// method2: map/ hashmap

void Program::mTokenize()
{
	char c;
	while(mFile.get(c))
	{
		if(mIsValidToken(c))
		{
			mProgTokens.push_back(c);
			
			if(c == '[')
			{
				mCheckBracketBalanceStack.push(std::make_pair(mNumLines, c));
			}
			if(c == ']')
			{
				if(! mCheckBracketBalanceStack.empty())
					mCheckBracketBalanceStack.pop();
				else
				{
					std::cerr << "[ERROR Line: " << mNumLines << "] unbalanced " << c << "\n";
					mNumErrors++;
				}
			}
			
			// std::cout << c << ".";
		}
		else if(mIsSpace(c))
		{
			/* ignore spaces, but increment mNumLines*/ 
			if(c == '\n')
				mNumLines++;
		}
		else if(mIsCommentLine(c))
		{
			/* ignore */
		}
		else
		{
			// error
			mNumErrors++;
			std::cerr << "[ERROR Line: " << mNumLines << "] invalid token '" << c << "'\n";
			
			if(mNumErrors > Config::maxNumErrorsShown)
			{
				std::cerr << "too many errors... exiting\n";
				exit(EXIT_FAILURE);
			}
		}
	}
	/* EOF reached */
}

void Program::mHandleErrors()
{
	if(! mCheckBracketBalanceStack.empty())
	{
		while(! mCheckBracketBalanceStack.empty())
		{
			std::cerr << "[ERROR Line: " << mCheckBracketBalanceStack.top().first << "] unbalanced " << mCheckBracketBalanceStack.top().second << "\n";
			mCheckBracketBalanceStack.pop();
		}
		exit(EXIT_FAILURE);
	}
	if(mNumErrors > 0)
		exit(EXIT_FAILURE);
}