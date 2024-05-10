#include "SceneTitle.h"
#include "SceneGame.h"
#include "DxLib.h"
#include "Camera.h"
SceneTitle::SceneTitle(SceneManager& sceneManager, DataManager& dataManager):
	SceneBase(sceneManager,dataManager)
{
	m_logoHandle = LoadGraph("data/image/titleImage.png");

	m_charactermodel[0] = MV1LoadModel("data/model/Player.mv1");
	m_charactermodel[1] = MV1LoadModel("data/model/Player.mv1");
	m_domemodel = MV1LoadModel("data/model/Dome.mv1");
	MV1SetScale(m_domemodel, VGet(20, 20, 20));

	m_pCamera = std::make_shared<Camera>();
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

void SceneTitle::Update()
{
	m_pCamera->Update();
	if (CheckHitKey(KEY_INPUT_G))
	{
		m_sceneManager.ChangeScene(std::make_shared<SceneGame>(m_sceneManager, m_dataManager));
	}
}

void SceneTitle::Draw()
{
	DrawString(0, 0, "SceneTitle", GetColor(255, 255, 255));
	MV1DrawModel(m_domemodel);
	DrawGraph(0, 0, m_logoHandle, true);

}

void SceneTitle::End()
{
}
