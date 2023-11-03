#pragma once
#include <vector>

// 前方宣言
class CommandBase;
class Stage;

class CommandManager {
private:
	std::vector<CommandBase*> commandListUndo_;	// Undo用リスト
	std::vector<CommandBase*> commandListRedo_;	// Redo用リスト
public:
	CommandManager();
	~CommandManager();

	// コマンドを記録
	void RecordCommand(CommandBase* command);
	void ClearCommand();
	void Undo(Stage* p);
	void Redo(Stage* p);
};