#include "CommandBase.h"

CommandBase::CommandBase(Stage* p, int x, int z, int size)
	:pStage_(p), selectBlock_(Block(x, z)), brushSize_(size)
{
}

CommandBase::~CommandBase() {
}