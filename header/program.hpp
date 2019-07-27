#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <cassert>

// #include "config.hpp"

class Program
{
public:
	Program(const std::string& path);
	~Program();
	std::string getFilePath() const;
	char getToken(unsigned int instrPtr) const;
	unsigned int getNumTokens() const;

private:
	bool mIsValidToken(char c) const;
	bool mIsSpace(char c) const;
	bool mIsCommentLine(char c);
	void mTokenize();
	void mHandleErrors();

private:
	std::vector<char> mProgTokens;
	std::stack<std::pair<unsigned int, char>> mCheckBracketBalanceStack;
	unsigned int mNumLines;
	unsigned int mNumErrors;
	std::string mFilePath;
	std::ifstream mFile;
};

