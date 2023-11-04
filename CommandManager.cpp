#include "CommandManager.h"
#include "CommandBase.h"

CommandManager::CommandManager() {
}

CommandManager::~CommandManager() {
	for (auto e : commandListUndo_) {
		delete e;
	}
	commandListUndo_.clear();
	for (auto e : commandListRedo_) {
		delete e;
	}
	commandListRedo_.clear();
}

void CommandManager::RecordCommand(CommandBase* command) {
	// Undoしているなら
	if (!commandListRedo_.empty()) {
		commandListRedo_.clear();
	}

	commandListUndo_.push_back(command);
}

void CommandManager::ClearCommand() {
	for (auto e : commandListUndo_) {
		delete e;
	}
	commandListUndo_.clear();
	for (auto e : commandListRedo_) {
		delete e;
	}
	commandListRedo_.clear();
}

void CommandManager::Undo(Stage* p) {
	// Undoリストが空じゃないなら
	if (!commandListUndo_.empty()) {
		commandListUndo_.back()->UndoCommand(p);
		// Redoにコピー
		commandListRedo_.push_back(commandListUndo_.back());
		commandListUndo_.pop_back();
	}
}

void CommandManager::Redo(Stage* p) {
	// Redoリストが空じゃないなら
	if (!commandListRedo_.empty()) {
		commandListRedo_.back()->RedoCommand(p);
		// Undoにコピー
		commandListUndo_.push_back(commandListRedo_.back());
		commandListRedo_.pop_back();
	}
}