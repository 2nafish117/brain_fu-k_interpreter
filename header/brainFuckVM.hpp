#pragma once

#include <string>
#include <cstring>
#include <cassert>

#include "program.hpp"
// #include "config.hpp"

class BrainFuckVM
{
public:
	BrainFuckVM();
	~BrainFuckVM();
	bool executeProgram(const Program& program);

private:
	void mExecuteInstruction(char token, const Program& program);
	void mIncrementDataPointer();
	void mDecrementDataPointer();
	void mIncrementDataByte();
	void mDecrementDataByte();
	void mOutputDataByte();
	void mInputDataByte();
	unsigned mSeekNextCorrespondingBranchEnd(const Program& program);
	bool mBeginLoopInstruction(const Program& program);
	bool mEndLoopInstruction();

private:
	// size of data buffer in bytes
	unsigned int mDataBuffSize;
	char* mDataPtr;
	char* mDataBuff;
	unsigned int mInstrPtr;
	// first stores '[' instrPointer, second stores corresponding ']' instrPointer
	std::stack<std::pair<unsigned int, unsigned int>> mLoopBranchStack;
};
