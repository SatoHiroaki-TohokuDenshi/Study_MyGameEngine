#pragma once
#include <vector>
#include "CommandBase.h"

enum BOX_TYPE;

class CommandChange
	: public CommandBase {
private:
	std::vector<BOX_TYPE> beforeBlockType_;
	BOX_TYPE afterBlockType_;
public:
	CommandChange(int x, int z, int size, BOX_TYPE after, Stage* p);
	~CommandChange();

	void UndoCommand(Stage* p) override;	//Undo
	void RedoCommand(Stage* p) override;	//Redo
};