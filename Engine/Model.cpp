#include "Model.h"
#include <vector>
#include "SafetyMacro.h"

using std::vector;

namespace Model {
	//データを格納する構造体
	struct ModelData {
		Fbx* pFbx_;				//FBXのアドレス
		Transform transform_;	//Transformの情報
		string fileName_;		//ファイルの名前

		//変数を初期化
		ModelData() :pFbx_(nullptr), transform_(Transform()), fileName_("") {};
	};

	vector<ModelData*> modelList_;

	int Load(string fileName) {
		ModelData* pData = new ModelData();
		for (auto& e : modelList_) {
			if (e->fileName_ == fileName) {
				pData->pFbx_ = e->pFbx_;
				break;
			}
		}

		if (pData->pFbx_ == nullptr) {
			//ファイルの読み込み
			pData->pFbx_ = new Fbx();
			if (FAILED(pData->pFbx_->Load(fileName)))
				return -1;
			pData->fileName_ = fileName;
		}
		modelList_.push_back(pData);
		//モデルのインデックス番号を返す
		return (int)modelList_.size() - 1;
	}

	void SetTransform(int hModel, Transform t) {
		modelList_.at(hModel)->transform_ = t;
	}

	void Draw(int hModel) {
		modelList_.at(hModel)->pFbx_->Draw(modelList_.at(hModel)->transform_);
	}

	void Release() {
		bool isRefferenced = false;	//参照されているか
		for (int i = 0; i < modelList_.size(); i++) {
			for (int j = i + 1; j < modelList_.size(); j++) {
				if (modelList_.at(i)->pFbx_ == modelList_.at(j)->pFbx_) {
					isRefferenced = true;
					break;
				}
			}
			if (isRefferenced == false) {
				SAFE_DELETE(modelList_.at(i)->pFbx_);
			}
			SAFE_DELETE(modelList_.at(i));
		}
		modelList_.clear();
	}
}