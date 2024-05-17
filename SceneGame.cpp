#include "SceneGame.h"
#include "SceneTitle.h"
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Obstruct.h"
#include "Ui.h"
namespace
{
	constexpr int kTimelimit = 30;//��������
	constexpr int kFramelate = 60;//�t���[�����[�g
	constexpr int kFinishDamage = 36;//�_���[�W�̌��E�l
}
SceneGame::SceneGame(SceneManager& sceneManager, DataManager& dataManager) :
	SceneBase(sceneManager, dataManager),
	m_isFinish(false),
	m_timer(kTimelimit),
	m_timeCount(0),
	m_isDraw(false)
{
	m_pPlayer = std::make_shared<Player>();
	m_pEnemy = std::make_shared<Enemy>();
	m_pCamera = std::make_shared<Camera>();
	m_pObstruct = std::make_shared<Obstruct>();
	m_pUi = std::make_shared<Ui>();
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_pPlayer->Init();
	m_pEnemy->Init();
	m_pObstruct->Init();
	m_pUi->Init();
}

void SceneGame::Update()
{

	m_pPlayer->Update(m_pEnemy);
	m_pEnemy->Update(m_pPlayer);
	m_pCamera->Update();
	m_pObstruct->Update();
	m_pUi->Update();
	//�Q�[�����I�����Ă��Ȃ����̏���
	if (!m_isFinish)
	{
		//���Ԃ��o�߂�����
		m_timeCount++;
		//60�t���[����������
		if (m_timeCount > kFramelate)
		{
			m_timeCount = 0;
			//�������Ԃ����炷
			m_timer--;
			//Ui�ɐ������Ԃ�n��
			m_pUi->SetTimer(m_timer);
		}
		//�^�C�}�[��0�b�ɂȂ�����
		if (m_timer <= 0)
		{
			//�����_�ŏ����Ă�������擾����
			if (m_pPlayer->GetDamage() > 0)
			{
				//�v���C���[�������ꍇ
				FinishGame(true);
			}
			else if (m_pPlayer->GetDamage() < 0)
			{
				//�G�l�~�[�������ꍇ
				FinishGame(false);
			}
			else
			{
				//���������������ꍇ
				DrawGame();
			}
		}
		//�_���[�W�����ʈȏ�󂯂���
		if (m_pPlayer->GetDamage() > kFinishDamage)
		{
			//�v���C���[�̏���
			FinishGame(true);
		}
		else if (m_pPlayer->GetDamage() < -kFinishDamage)
		{
			//�G�l�~�[���̏���
			FinishGame(false);
		}
	}
	else
	{
		if (CheckHitKeyAll() && m_pUi->GetFinishStaging())
		{
			m_sceneManager.ChangeScene(std::make_shared<SceneTitle>(m_sceneManager, m_dataManager));
			return;
		}
	}
}

void SceneGame::Draw()
{
	m_pPlayer->Draw();
	m_pEnemy->Draw();
	m_pObstruct->Draw();
	m_pUi->Draw();
	DrawString(0, 0, "SceneGame", GetColor(255, 255, 255));
}

void SceneGame::End()
{
}

void SceneGame::FinishGame(bool player)
{
	m_pPlayer->SetFinish(player);
	m_pEnemy->SetFinish(player);
	m_pUi->SetFinish(player);
	m_isFinish = true;
	if (player)
	{
		m_pCamera->SetWinner(m_pPlayer->GetPos());
	}
	else
	{
		m_pCamera->SetWinner(m_pEnemy->GetPos());
	}
}

void SceneGame::DrawGame()
{
	m_isFinish = true;
	m_isDraw = true;

	m_pPlayer->SetDraw();
	m_pEnemy->SetDraw();
	m_pUi->SetDraw();
}
