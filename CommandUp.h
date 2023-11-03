#pragma once
#include "CommandBase.h"

class CommandUp
	: public CommandBase {
private:

public:
	CommandUp(int x, int y, int size);
	~CommandUp();

	void UndoCommand(Stage* p) override;	//Undo
	void RedoCommand(Stage* p) override;	//Redo
};