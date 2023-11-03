#include "CommandUp.h"
#include "Stage.h"

CommandUp::CommandUp(Stage* p, int x, int y, int size)
	:CommandBase(p, x, y, size)
{
}

CommandUp::~CommandUp() {
}

void CommandUp::UndoCommand() {
	// 選んだブロックを下げる
	switch (brushSize_) {
	case brushS:
		pStage_->SetBlockHeight(selectBlock_.x_, selectBlock_.z_,
			pStage_->GetBlockHeight(selectBlock_.x_, selectBlock_.z_) - 1);
		break;
	case brushM:
		for (int x = -1; x < 2; x++) {
			for (int z = -1; z < 2; z++) {
				if (selectBlock_.x_ + x < 0 || selectBlock_.x_ + x >= sizeX ||
					selectBlock_.z_ + z < 0 || selectBlock_.z_ + z >= sizeZ) {
					continue;
				}
				pStage_->SetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z,
					pStage_->GetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z) - 1);
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
				pStage_->SetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z,
					pStage_->GetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z) - 1);
			}
		}
		break;
	default:
		break;
	}
}

void CommandUp::RedoCommand() {
	// 選んだブロックを上げる
	switch (brushSize_) {
	case brushS:
		pStage_->SetBlockHeight(selectBlock_.x_, selectBlock_.z_,
			pStage_->GetBlockHeight(selectBlock_.x_, selectBlock_.z_) + 1);
		break;
	case brushM:
		for (int x = -1; x < 2; x++) {
			for (int z = -1; z < 2; z++) {
				if (selectBlock_.x_ + x < 0 || selectBlock_.x_ + x >= sizeX ||
					selectBlock_.z_ + z < 0 || selectBlock_.z_ + z >= sizeZ) {
					continue;
				}
				pStage_->SetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z,
					pStage_->GetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z) + 1);
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
				pStage_->SetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z,
					pStage_->GetBlockHeight(selectBlock_.x_ + x, selectBlock_.z_ + z) + 1);
			}
		}
		break;
	default:
		break;
	}
}
