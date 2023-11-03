#pragma once
#include <vector>
#include "CommandBase.h"

class CommandChange
	: public CommandBase {
private:
	std::vector<int> blockType_;
public:
	CommandChange(Stage* p, int x, int z, int size);
	~CommandChange();

	void UndoCommand();	//Undo
	void RedoCommand();	//Redo
};