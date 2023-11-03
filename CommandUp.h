#pragma once
#include "CommandBase.h"

class CommandUp
	: public CommandBase {
private:

public:
	CommandUp(Stage* p, int x, int y, int size);
	~CommandUp();

	void UndoCommand() override;	//Undo
	void RedoCommand() override;	//Redo
};