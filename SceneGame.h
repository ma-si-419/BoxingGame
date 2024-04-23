#pragma once
#include "SceneBase.h"
#include <memory>

class CharacterBase;
class SceneGame : public SceneBase
{
public:
	SceneGame(SceneManager& sceneManager, DataManager& dataManager);
	~SceneGame();
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//終了処理
	void End();
private:
	
	std::shared_ptr<CharacterBase> m_pPlayer;

};

