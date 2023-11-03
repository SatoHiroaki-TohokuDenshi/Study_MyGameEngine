#pragma once

// 前方宣言
class Stage;

namespace {
	struct Block {
		int x_;
		int z_;
		Block(int x, int z) {
			x_ = x;
			z_ = z;
		}
	};
}

class CommandBase {
protected:
	Block selectBlock_;	//選択されたブロック
	int brushSize_;		//ブラシの大きさ
public:
	CommandBase(int x, int z, int size);
	~CommandBase();

	virtual void UndoCommand(Stage* p) = 0;	//Undo
	virtual void RedoCommand(Stage* p) = 0;	//Redo
};