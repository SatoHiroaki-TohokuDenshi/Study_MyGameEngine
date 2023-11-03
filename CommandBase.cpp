#include "CommandBase.h"

CommandBase::CommandBase(int x, int z, int size)
	:selectBlock_(Block(x, z)), brushSize_(size)
{
}

CommandBase::~CommandBase() {
}