#include "Ui.h"
#include "Game.h"
#include <string>
namespace
{
	constexpr int kTimelimit = 30;//��������

	constexpr int kTimerScale = 30;//�^�C�}�[�̕����̑傫��

	/*�^�C�}�[�̍��W*/
	constexpr int kTimerPosX = 250;
	constexpr int kTimerPosY = 10;

	/*�����I�����̉摜�֌W*/
	constexpr double kStagingGraphInitSize = 10.0;//�����T�C�Y
	constexpr double kStagingSpeed = 0.3;	//�k���X�s�[�h
	constexpr int kStagingShakeTime = 2;	//�h�炷����
	constexpr int kStagingShakeScale = 40;	//�h��̑傫��

}
Ui::Ui() :
	m_isFinish(false),
	m_timer(kTimelimit),
	m_isWinPlayer(false),
	m_isDraw(false),
	m_stagingGraphScale(kStagingGraphInitSize),
	m_isStagingGraphShake(true),
	m_shakeTime(0),
	m_isPad(true)
{
	m_stagingGraphPos = VGet(Game::kWindowWidth / 2, Game::kWindowHeight / 2, 0);

	m_winPlayerGraph = LoadGraph("data/image/winPlayer.png");
	m_winEnemyGraph = LoadGraph("data/image/winEnemy.png");
	m_drawGraph = LoadGraph("data/image/draw.png");
	m_keyManualGraph = LoadGraph("data/image/keyManual.png");
	m_padManualGraph = LoadGraph("data/image/padManual.png");

	m_timerMap['0'] = LoadGraph("data/image/zero.png");
	m_timerMap['1'] = LoadGraph("data/image/one.png");
	m_timerMap['2'] = LoadGraph("data/image/two.png");
	m_timerMap['3'] = LoadGraph("data/image/three.png");
	m_timerMap['4'] = LoadGraph("data/image/four.png");
	m_timerMap['5'] = LoadGraph("data/image/five.png");
	m_timerMap['6'] = LoadGraph("data/image/six.png");
	m_timerMap['7'] = LoadGraph("data/image/seven.png");
	m_timerMap['8'] = LoadGraph("data/image/eight.png");
	m_timerMap['9'] = LoadGraph("data/image/nine.png");
}

Ui::~Ui()
{
}

void Ui::Init()
{

}

void Ui::Update()
{
	//�Q�[�����I��������
	if (m_isDraw || m_isFinish)
	{

		//�k���������Ȃ��悤��
		if (m_stagingGraphScale > 1.0)
		{
			m_stagingGraphScale -= kStagingSpeed;
		}
		//�k������������
		else if (m_isStagingGraphShake)
		{
			//���������h�炷
			m_stagingGraphPos.x += GetRand(kStagingShakeScale) - kStagingShakeScale / 2;
			m_stagingGraphPos.y += GetRand(kStagingShakeScale) - kStagingShakeScale / 2;

			m_shakeTime++;
			//��莞�ԗh�炵����
			if (m_shakeTime > kStagingShakeTime)
			{
				//�h����~�߂�
				m_isStagingGraphShake = false;
				//�ŏ��̍��W�ɖ߂�
				m_stagingGraphPos = VGet(Game::kWindowWidth / 2, Game::kWindowHeight / 2, 0);
			}
		}
	}
}

void Ui::Draw()
{
	/*��ɕ\������*/
	if (m_isPad)
	{
		DrawGraph(0, 0, m_padManualGraph, true);
	}
	else
	{
		DrawGraph(0, 0, m_keyManualGraph, true);
	}
	DrawTimer();

	/*�Q�[���I���������̉��o*/
	if (m_isFinish)
	{
		if (m_isWinPlayer)
		{
			DrawRotaGraph(m_stagingGraphPos.x, m_stagingGraphPos.y, m_stagingGraphScale, 0, m_winPlayerGraph, true);
		}
		else
		{
			DrawRotaGraph(m_stagingGraphPos.x, m_stagingGraphPos.y, m_stagingGraphScale, 0, m_winEnemyGraph, true);
		}
	}
	//���������ŏI��������̉��o
	if (m_isDraw)
	{
		DrawRotaGraph(m_stagingGraphPos.x, m_stagingGraphPos.y, m_stagingGraphScale, 0, m_drawGraph, true);
	}

}

void Ui::DrawTimer()
{
	//�^�C�}�[�������b���擾
	std::string timeNumber = std::to_string(m_timer);
	//�ꌅ�ڂ�char�^�ɕۑ�
	char temp = timeNumber.at(0);
	//�^�C�}�[���ꌅ�̏ꍇ
	if (m_timer < 10)
	{
		//�摜����\�����邾��
		DrawGraph(kTimerPosX, kTimerPosY, m_timerMap[temp], true);
	}
	//�^�C�}�[���񌅂̏ꍇ
	else
	{
		//�񌅖ڂ̐�����char�^�ɕۑ�
		char temp2 = timeNumber.at(1);
		//�摜���\������
		DrawGraph(kTimerPosX - kTimerScale, kTimerPosY, m_timerMap[temp], true);
		DrawGraph(kTimerPosX + kTimerScale, kTimerPosY, m_timerMap[temp2], true);
	}
}

void Ui::DrawCountDown(int time)
{
	//�^�C�}�[�������b���擾
	std::string timeNumber = std::to_string(time);
	//�ꌅ�ڂ�char�^�ɕۑ�
	char temp = timeNumber.at(0);
	//�摜��\������
	DrawRotaGraph(Game::kWindowWidth / 2,Game::kWindowHeight / 2,2.0,0.0, m_timerMap[temp], true);
}
