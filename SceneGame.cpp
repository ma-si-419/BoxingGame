#include "SceneGame.h"
#include "DxLib.h"
#include "Player.h"

SceneGame::SceneGame(SceneManager& sceneManager, DataManager& dataManager):
	SceneBase(sceneManager,dataManager)
{
	m_pPlayer = std::make_shared<Player>();
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_pPlayer->Init();
}

void SceneGame::Update()
{
	m_pPlayer->Update();
}

void SceneGame::Draw()
{
	m_pPlayer->Draw();
	DrawString(0, 0, "SceneGame", GetColor(255, 255, 255));
}

void SceneGame::End()
{
}
