#include "SceneTitle.h"
#include "SceneGame.h"
#include "DxLib.h"
SceneTitle::SceneTitle(SceneManager& sceneManager, DataManager& dataManager):
	SceneBase(sceneManager,dataManager)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

void SceneTitle::Update()
{
	if (CheckHitKey(KEY_INPUT_G))
	{
		m_sceneManager.ChangeScene(std::make_shared<SceneGame>(m_sceneManager, m_dataManager));
	}
}

void SceneTitle::Draw()
{
	DrawString(0, 0, "SceneTitle", GetColor(255, 255, 255));
}

void SceneTitle::End()
{
}
