#pragma once
#include "SceneBase.h"
#include <memory>

class battleManager;
class CharacterBase;
class SceneGame : public SceneBase
{
public:
	SceneGame(SceneManager& sceneManager, DataManager& dataManager);
	~SceneGame();
	//‰Šú‰»ˆ—
	void Init();
	//XVˆ—
	void Update();
	//•`‰æˆ—
	void Draw();
	//I—¹ˆ—
	void End();
private:
	
	std::shared_ptr<CharacterBase> m_pPlayer;
	std::shared_ptr<CharacterBase> m_pEnemy;
	std::shared_ptr<battleManager> m_pBattleManager;

};

