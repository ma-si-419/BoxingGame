#pragma once
#include "SceneBase.h"
class SceneTitle : public SceneBase
{
public:
	SceneTitle(SceneManager& sceneManager, DataManager& dataManager);
	~SceneTitle();
	//‰Šú‰»ˆ—
	void Init();
	//XVˆ—
	void Update();
	//•`‰æˆ—
	void Draw();
	//I—¹ˆ—
	void End();
};