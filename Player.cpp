#include "Player.h"
Player::Player()
{
	m_model = MV1LoadModel("data/model/Player.mv1");
	ChangeAnim(anim::kIdle);

	m_pos = VGet(-baseConstant::kEnemyLange, 0, 0);
	MV1SetRotationXYZ(m_model, VGet(0, static_cast<float> ((DX_PI_F / 180) * 270), 0));
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update(std::shared_ptr<CharacterBase> enemy)
{
	//������^�C�~���O��������
	if (!m_isGap)
	{
		//�p���`�{�^�����������Ƃ�
		if (CheckHitKey(KEY_INPUT_Z) && !m_isHitKey && !m_isPunch)
		{
			ChangeAnim(anim::kPunch);
			m_isPunch = true;
			m_isHitKey = true;
			//���肪�p���`��ł��Ă����Ԃ�������p���`�̑��x��������
			m_isCounter = enemy->GetPunchState();
		}
		//�K�[�h�{�^�����������Ƃ�
		if (CheckHitKey(KEY_INPUT_X) && !m_isHitKey)
		{
			ChangeAnim(anim::kGuard);
			m_isHitKey = true;
			m_isGuard = true;
			m_isPunch = false;
		}
		//�K�[�h�{�^���𗣂����Ƃ�
		else if (!CheckHitKey(KEY_INPUT_X) && m_isGuard)
		{
			//�K�[�h����߂鏈��������
			ChangeAnim(anim::kIdle);
			m_isGuard = false;
		}
		//�p���`�{�^���ƃK�[�h�{�^���𗣂�����
		if (!CheckHitKey(KEY_INPUT_Z) && !CheckHitKey(KEY_INPUT_X))
		{
			m_isHitKey = false;
		}
	}

	m_animTime += m_animPlaySpeed;
	//�A�j���[�V�����̍Đ����Ԃ��ő�܂ł�������
	if (m_animTime > m_totalAnimTime)
	{
		m_animTime = 0;
		if (m_playAnim == anim::kPunch || m_playAnim == anim::kHitReaction)
		{
			ChangeAnim(anim::kIdle);
		}
		else if (m_playAnim == anim::kGuard)
		{
			m_animTime = m_totalAnimTime;
		}
	}
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
	MV1SetAttachAnimTime(m_model, m_attachAnim, m_animTime);
	MV1SetPosition(m_model, m_pos);
}

void Player::Draw()
{
	MV1DrawModel(m_model);
	DrawFormatString(100, 100, GetColor(255, 255, 255), "P%d", m_damage);
}

CharacterBase::damageKind Player::OnDamage(bool counter)
{
	CharacterBase::damageKind ans;
	//�K�[�h���Ă�����
	if (m_isGuard)
	{
		m_damage -= baseConstant::kGuardDamage;
		m_gapTime = baseConstant::kGuardGapTime;
		ans = damageKind::kGuard;
	}
	//�J�E���^�[�̃^�C�~���O
	else if (counter)
	{
		m_damage -= baseConstant::kCounterDamage;
		m_gapTime = baseConstant::kHitGapTime;
		ChangeAnim(anim::kHitReaction);
		ans = damageKind::kCounter;
	}
	//���ʂɃq�b�g
	else
	{
		m_damage -= baseConstant::kHitDamage;
		m_gapTime = baseConstant::kHitGapTime;
		ChangeAnim(anim::kHitReaction);
		ans = damageKind::kHit;
	}
	m_pos.x = baseConstant::kDamageLange * -m_damage + baseConstant::kEnemyLange;
	m_isPunch = false;
	m_punchTime = 0;
	return ans;
}

void Player::HitPunch(damageKind kind)
{
	if (kind == damageKind::kHit)
	{
		m_gapTime = baseConstant::kHitPunchGapTime;
		m_damage += baseConstant::kHitDamage;
	}
	else if (kind == damageKind::kGuard)
	{
		m_gapTime = baseConstant::kGuardHitGapTime;
		m_damage += baseConstant::kGuardDamage;
	}
	else if (kind == damageKind::kCounter)
	{
		m_gapTime = baseConstant::kHitGapTime;
		m_damage += baseConstant::kCounterDamage;
	}
}

void Player::SetDamagePos()
{
	m_pos.x = baseConstant::kDamageLange * m_damage - baseConstant::kEnemyLange;
}
