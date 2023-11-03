#include "CommandDown.h"
#include "Stage.h"

CommandDown::CommandDown(int x, int y, int size)
	:CommandBase(x, y, size)
{
}

CommandDown::~CommandDown() {
}

void CommandDown::UndoCommand(Stage* p) {
	// 選んだブロックを上げる
	switch (brushSize_) {
	case brushS:
		p->SetBlockHeight(selectBlock_.x_, selectBlock_.z_,
			p->GetBlockHeight(selectBlock_.x_, selectBlock_.z_) + 1);
		break;
	case brushM:
		for (int x = -1; x < 2; x++) {
			for (int z = -1; z < 2; z++) {
				if (selectBlock_.x_ + x < 0 || selectBlock_.x_ + x >= sizeX ||
					selectBlock_.z_ + z < 0 || selectBlock_.z_ + z >= sizeZ) {
					continue;
				}
				p->SetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z,
					p->GetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z) + 1);
			}
		}
		break;
	case brushL:
		for (int x = -2; x < 3; x++) {
			for (int z = -2; z < 3; z++) {
				if (selectBlock_.x_ + x < 0 || selectBlock_.x_ + x >= sizeX ||
					selectBlock_.z_ + z < 0 || selectBlock_.z_ + z >= sizeZ) {
					continue;
				}
				p->SetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z,
					p->GetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z) + 1);
			}
		}
		break;
	default:
		break;
	}
}

void CommandDown::RedoCommand(Stage* p) {
	// 選んだブロックを下げる
	switch (brushSize_) {
	case brushS:
		p->SetBlockHeight(selectBlock_.x_, selectBlock_.z_,
			p->GetBlockHeight(selectBlock_.x_, selectBlock_.z_) - 1);
		break;
	case brushM:
		for (int x = -1; x < 2; x++) {
			for (int z = -1; z < 2; z++) {
				if (selectBlock_.x_ + x < 0 || selectBlock_.x_ + x >= sizeX ||
					selectBlock_.z_ + z < 0 || selectBlock_.z_ + z >= sizeZ) {
					continue;
				}
				p->SetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z,
					p->GetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z) - 1);
			}
		}
		break;
	case brushL:
		for (int x = -2; x < 3; x++) {
			for (int z = -2; z < 3; z++) {
				if (selectBlock_.x_ + x < 0 || selectBlock_.x_ + x >= sizeX ||
					selectBlock_.z_ + z < 0 || selectBlock_.z_ + z >= sizeZ) {
					continue;
				}
				p->SetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z,
					p->GetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z) - 1);
			}
		}
		break;
	default:
		break;
	}
}
