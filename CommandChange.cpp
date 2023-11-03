#include "CommandChange.h"
#include "Stage.h"

CommandChange::CommandChange(int x, int z, int size, BOX_TYPE after, Stage* p)
	:CommandBase(x, z, size), afterBlockType_(after)
{
	// ブロックを取得
	beforeBlockType_.resize(brushSize_ * brushSize_);

	switch (brushSize_) {
	case brushS:
		beforeBlockType_.push_back(p->GetBlockType(selectBlock_.x_, selectBlock_.z_));
		break;
	case brushM:
		for (int x = -1; x < 2; x++) {
			for (int z = -1; z < 2; z++) {
				if (selectBlock_.x_ + x < 0 || selectBlock_.x_ + x >= sizeX ||
					selectBlock_.z_ + z < 0 || selectBlock_.z_ + z >= sizeZ) {
					continue;
				}
				beforeBlockType_.push_back(p->GetBlockType(selectBlock_.x_ + x, selectBlock_.z_ + z));
			}
		}
		break;
	case brushL:
		for (int x = -2; x < 3; x++) {
			for (int z = -2; z < 3; z++) {
				if (selectBlock_.x_ + x < 0 || selectBlock_.x_ + x >= sizeX ||
					selectBlock_.z_ + z < 0 || selectBlock_.z_ + z >= sizeZ) {
					beforeBlockType_.push_back(BOX_TYPE::BOX_MAX);
					continue;
				}
				beforeBlockType_.push_back(p->GetBlockType(selectBlock_.x_ + x, selectBlock_.z_ + z));
			}
		}
		break;
	default:
		break;
	}

}

CommandChange::~CommandChange() {
}

void CommandChange::UndoCommand(Stage* p) {
	// 選んだブロックを戻す
	switch (brushSize_) {
	case brushS:
		p->SetBlock(selectBlock_.x_, selectBlock_.z_, beforeBlockType_[0]);
		break;
	case brushM:
		int index = 0;
		for (int x = -1; x < 2; x++) {
			for (int z = -1; z < 2; z++) {
				if (selectBlock_.x_ + x < 0 || selectBlock_.x_ + x >= sizeX ||
					selectBlock_.z_ + z < 0 || selectBlock_.z_ + z >= sizeZ) {
					continue;
				}
				p->SetBlock(selectBlock_.x_ + x, selectBlock_.z_ + z, beforeBlockType_[index]);
			}
		}
		break;
	case brushL:
		int index = 0;
		for (int x = -2; x < 3; x++) {
			for (int z = -2; z < 3; z++) {
				if (selectBlock_.x_ + x < 0 || selectBlock_.x_ + x >= sizeX ||
					selectBlock_.z_ + z < 0 || selectBlock_.z_ + z >= sizeZ) {
					continue;
				}
				p->SetBlock(selectBlock_.x_ + x, selectBlock_.z_ + z, beforeBlockType_[index]);
			}
		}
		break;
	default:
		break;
	}
}

void CommandChange::RedoCommand(Stage* p) {
	// 選んだブロックを変える
	switch (brushSize_) {
	case brushS:
		p->SetBlock(selectBlock_.x_, selectBlock_.z_, beforeBlockType_[0]);
		break;
	case brushM:
		int index = 0;
		for (int x = -1; x < 2; x++) {
			for (int z = -1; z < 2; z++) {
				if (selectBlock_.x_ + x < 0 || selectBlock_.x_ + x >= sizeX ||
					selectBlock_.z_ + z < 0 || selectBlock_.z_ + z >= sizeZ) {
					continue;
				}
				p->SetBlock(selectBlock_.x_ + x, selectBlock_.z_ + z,afterBlockType_);
			}
		}
		break;
	case brushL:
		int index = 0;
		for (int x = -2; x < 3; x++) {
			for (int z = -2; z < 3; z++) {
				if (selectBlock_.x_ + x < 0 || selectBlock_.x_ + x >= sizeX ||
					selectBlock_.z_ + z < 0 || selectBlock_.z_ + z >= sizeZ) {
					continue;
				}
				p->SetBlock(selectBlock_.x_ + x, selectBlock_.z_ + z, afterBlockType_);
			}
		}
		break;
	default:
		break;
	}
}
