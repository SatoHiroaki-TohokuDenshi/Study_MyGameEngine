#pragma once
#include "CommandBase.h"

class CommandDown
	: public CommandBase {
private:

public:
	CommandDown(int x, int y, int size);
	~CommandDown();

	void UndoCommand(Stage* p) override;	//Undo
	void RedoCommand(Stage* p) override;	//Redo
};