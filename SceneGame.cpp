#include "SceneGame.h"
#include "DxLib.h"
#include "Player.h"
#include "battleManager.h"

SceneGame::SceneGame(SceneManager& sceneManager, DataManager& dataManager):
	SceneBase(sceneManager,dataManager)
{
	m_pPlayer = std::make_shared<Player>();
	m_pEnemy = std::make_shared<Player>();
	m_pBattleManager = std::make_shared<battleManager>(m_pPlayer,m_pEnemy);
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_pPlayer->Init();
	m_pBattleManager->Init();
}

void SceneGame::Update()
{
	m_pPlayer->Update(m_pBattleManager);
	m_pBattleManager->Update();
}

void SceneGame::Draw()
{
	m_pPlayer->Draw();
	DrawString(0, 0, "SceneGame", GetColor(255, 255, 255));
}

void SceneGame::End()
{
}
