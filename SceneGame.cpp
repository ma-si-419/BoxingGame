#include "SceneGame.h"
#include "SceneTitle.h"
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"


SceneGame::SceneGame(SceneManager& sceneManager, DataManager& dataManager):
	SceneBase(sceneManager,dataManager)
{
	m_pPlayer = std::make_shared<Player>();
	m_pEnemy = std::make_shared<Enemy>();
	m_pCamera = std::make_shared<Camera>();
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_pPlayer->Init();
	m_pEnemy->Init();
}

void SceneGame::Update()
{

	m_pPlayer->Update(m_pEnemy);
	m_pEnemy->Update(m_pPlayer);
	m_pCamera->Update();

	if (CheckHitKey(KEY_INPUT_T))
	{
		m_sceneManager.ChangeScene(std::make_shared<SceneTitle>(m_sceneManager, m_dataManager));
	}
}

void SceneGame::Draw()
{
	m_pPlayer->Draw();
	m_pEnemy->Draw();
	DrawString(0, 0, "SceneGame", GetColor(255, 255, 255));
}

void SceneGame::End()
{
}
