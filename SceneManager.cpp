#include "SceneManager.h"
#include "SceneTitle.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	m_pScene->Update();
}

void SceneManager::Draw()
{
	m_pScene->Draw();
}
void SceneManager::ChangeScene(std::shared_ptr<SceneBase> next)
{
	if (m_pScene)
	{
		m_pScene->End();
	}
	m_pScene = next;
	m_pScene->Init();
}
