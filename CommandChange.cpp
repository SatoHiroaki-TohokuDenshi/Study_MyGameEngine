#include "CommandChange.h"

CommandChange::CommandChange(Stage* p, int x, int z, int size)
	:CommandBase(p, x, z, size)
{
	// ブロックを取得
	blockType_.resize(brushSize_ * brushSize_);

	//p->GetBlockType(selectBlock_.x_, selectBlock_.z_);
}

CommandChange::~CommandChange() {
}

void CommandChange::UndoCommand() {
	// 選んだブロックを戻す
}

void CommandChange::RedoCommand() {
	// 選んだブロックを変える
}
