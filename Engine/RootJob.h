#pragma once
#include "GameObject.h"

class RootJob : public GameObject {
public:
	RootJob(GameObject* parent);
	~RootJob();

	//‰Šú‰»
	void Initialize() override;
	//XV
	void Update() override;
	//•`‰æ
	void Draw() override;
	//‰ğ•ú
	void Release() override;
};

