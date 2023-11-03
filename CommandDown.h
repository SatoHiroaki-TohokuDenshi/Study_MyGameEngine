#pragma once
#include "CommandBase.h"

class CommandDown
	: public CommandBase {
private:

public:
	CommandDown(Stage* p, int x, int y, int size);
	~CommandDown();

	void UndoCommand() override;	//Undo
	void RedoCommand() override;	//Redo
};