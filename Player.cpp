#include "Player.h"
#include "Input.h"

namespace
{
	constexpr float kFallSpeed = 4.5f;
	constexpr int kFinishDamage = 36;
}

Player::Player()
{
	m_model = MV1LoadModel("data/model/Player.mv1");
	ChangeAnim(anim::kIdle);

	m_pos = VGet(-baseConstant::kEnemyLange, 0, 0);
	MV1SetRotationXYZ(m_model, VGet(0, static_cast<float> ((DX_PI_F / 180) * 270), 0));
	//1P���Ɛݒ�
	m_isPlayer = true;
}

Player::~Player()
{
	MV1DeleteModel(m_model);
}

void Player::Init()
{
	MV1SetPosition(m_model, m_pos);
}

void Player::Update(std::shared_ptr<CharacterBase> enemy,Input input)
{
	//������^�C�~���O��������
	if (!m_isGap && !m_isFinishGame)
	{
		//�K�[�h�{�^�����������Ƃ�
		if (input.IsPress("leftShoulder") && !m_isHitGuardKey)
		{
			ChangeAnim(anim::kGuard);
			m_isGuard = true;
			m_isHitGuardKey = true;
			m_isPunch = false;
		}
		//�p���`�{�^�����������Ƃ�
		if (input.IsTrigger("leftTrigger") && !m_isPunch)
		{
			ChangeAnim(anim::kPunch);
			m_isPunch = true;
			m_isGuard = false;
			//���肪�p���`��ł��Ă����Ԃ�������p���`�̑��x��������
			m_isCounter = enemy->GetPunchState();
		}
		//�K�[�h�{�^���������ꂽ�Ƃ��̏���
		if (!CheckHitKey(KEY_INPUT_X))
		{
			m_isHitGuardKey = false;
			//�K�[�h���Ă�����
			if (m_isGuard)
			{
				//�K�[�h����߂鏈��������
				ChangeAnim(anim::kIdle);
				m_isGuard = false;
			}
		}
	}

	//�A�j���[�V��������
	PlayAnim();
	//�p���`�̏���
	if (m_isPunch)
	{
		//�J�E���^�[�������ꍇ�p���`��������܂ł̃X�s�[�h�𑬂߂�
		if (m_isCounter)
		{
			m_punchTime += baseConstant::kCounterPunchSpeed;
		}
		else
		{
			m_punchTime++;
		}
	}
	else
	{
		m_punchTime = 0;
	}

	if (m_punchTime > baseConstant::kPunchHitTime)
	{
		CharacterBase::damageKind hitKind;
		hitKind = enemy->OnDamage(m_isCounter);
		HitPunch(hitKind);
		SetDamagePos();
		enemy->SetDamagePos();
		m_isPunch = false;
		m_punchTime = 0;
	}

	//�d���Ǘ�
	m_gapTime--;
	if (m_gapTime < 0)
	{
		m_isGap = false;
	}
	else
	{
		m_isGap = true;
	}
	//�������I��������̏���
	if (m_isFinishGame)
	{
		//�����ɕ����Ă�����
		if (m_damage < -kFinishDamage)
		{
			//���ɗ����Ă�������������
			m_pos.y -= kFallSpeed;
		}
	}

	MV1SetAttachAnimTime(m_model, m_attachAnim, m_animTime);
	MV1SetPosition(m_model, m_pos);
}

void Player::Draw()
{
	MV1DrawModel(m_model);
}
