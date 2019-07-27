#include "brainFuckVM.hpp"
#include "config.hpp"

BrainFuckVM::BrainFuckVM()
: mDataBuffSize(Config::bufferSizeInBytes), mInstrPtr(Config::initialDataPointerPosition)
{
	mDataBuff = new char[mDataBuffSize];
	memset(mDataBuff, 0, mDataBuffSize);
	mDataPtr = mDataBuff;
}

BrainFuckVM::~BrainFuckVM()
{
	delete[] mDataBuff;
	mDataPtr = nullptr;
	std::cout << "\nBrainFuckVM shut down Normally." << std::endl;
	std::cout.flush();
}

bool BrainFuckVM::executeProgram(const Program& program)
{
	std::cout << "executing " << program.getFilePath() << "\n\n";
	
	while(mInstrPtr < program.getNumTokens())
	{
		char token = program.getToken(mInstrPtr);
		mExecuteInstruction(token, program);
	}

	return true;
}

void BrainFuckVM::mExecuteInstruction(char token, const Program& program)
{
	switch(token)
	{
	case '>': 
		mIncrementDataPointer();
		break;
	case '<': 
		mDecrementDataPointer();
		break;
	case '+': 
		mIncrementDataByte();
		break;
	case '-': 
		mDecrementDataByte();
		break;
	case '.': 
		mOutputDataByte();
		break;
	case ',': 
		mInputDataByte();
		break;
	case '[': 
		mBeginLoopInstruction(program);
		break;
	case ']': 
		mEndLoopInstruction();
		break;
	default:
		std::cerr << "how tf did you get token " << token << "\n";
	}
}

void BrainFuckVM::mIncrementDataPointer()
{
	++mDataPtr;
	// @Fix: replace assert with something like
	/*
		>>>
		[Error Line: lineNo] index out of range 
	*/
	assert(std::distance(mDataPtr, mDataBuff) < mDataBuffSize);
	++mInstrPtr;
}

void BrainFuckVM::mDecrementDataPointer()
{
	--mDataPtr;
	// @Fix: replace assert with something like
	/*
		>>>
		[Error Line: lineNo] index out of range 
	*/
	assert(mDataPtr >= mDataBuff);
	++mInstrPtr;
}

void BrainFuckVM::mIncrementDataByte()
{
	++(*mDataPtr);
	++mInstrPtr;
}

void BrainFuckVM::mDecrementDataByte()
{
	--(*mDataPtr);
	++mInstrPtr;
}

void BrainFuckVM::mOutputDataByte()
{
	if(Config::showNumInsteadOfChar)
		std::cout << (int) *mDataPtr << " ";
	else
		std::cout << *mDataPtr;
	++mInstrPtr;
}

void BrainFuckVM::mInputDataByte()
{
	int val;
	std::cin >> val;
	*mDataPtr = (char)val;
	++mInstrPtr;
}

// do not call anywhere other than mBeginLoopInstruction(), possible make a lambda?
unsigned int BrainFuckVM::mSeekNextCorrespondingBranchEnd(const Program& program)
{
	unsigned int stack = 0;
	unsigned int instrPtr = mInstrPtr;
	while(true)
	{
		char token = program.getToken(instrPtr);
		if(token == '[')
			stack++;
		if(token == ']')
			stack--;
		if(stack == 0)
			return instrPtr;
		
		++instrPtr;
	}
	return instrPtr;
}

bool BrainFuckVM::mBeginLoopInstruction(const Program& program)
{
	// put the loop frame on stack, if first encounter with '[' or stack is empty
	if(mLoopBranchStack.empty() || mInstrPtr != mLoopBranchStack.top().first)
	{
		unsigned int endLoopInstrPtr = mSeekNextCorrespondingBranchEnd(program);
		mLoopBranchStack.push(std::make_pair(mInstrPtr, endLoopInstrPtr));
	}

	if(*mDataPtr == 0)
	{
		// seek to the instruction after ']' when loop condition fails
		mInstrPtr = mLoopBranchStack.top().second + 1;
		mLoopBranchStack.pop();
		return false;
	}
	// loop condition success, continue as usual...nothing to see here, move on!
	++mInstrPtr;
	return true;
}

bool BrainFuckVM::mEndLoopInstruction()
{
	// unconditionally jump back to the corresponding '[' if stack not empty
	if(! mLoopBranchStack.empty())
		mInstrPtr = mLoopBranchStack.top().first;
}