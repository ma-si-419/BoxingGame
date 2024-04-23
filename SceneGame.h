#pragma once
#include "SceneBase.h"
#include <memory>

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

};

