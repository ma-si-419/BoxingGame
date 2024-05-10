#include "Enemy.h"
Enemy::Enemy()
{
	m_model = MV1LoadModel("data/model/Player.mv1");
	ChangeAnim(anim::kIdle);

	m_pos = VGet(baseConstant::kEnemyLange, 0, 0);
	MV1SetRotationXYZ(m_model, VGet(0, static_cast<float> ((DX_PI_F / 180) * 90), 0));
}
Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update(std::shared_ptr<CharacterBase> player)
{
	//������^�C�~���O��������
	if (!m_isGap)
	{
		//�p���`�{�^�����������Ƃ�
		if (CheckHitKey(KEY_INPUT_O) && !m_isHitKey && !m_isPunch)
		{
			ChangeAnim(anim::kPunch);
			m_isPunch = true;
			m_isHitKey = true;
			//���肪�p���`��ł��Ă����Ԃ�������p���`�̑��x��������
			m_isCounter = player->GetPunchState();
		}
		if (CheckHitKey(KEY_INPUT_P) && !m_isHitKey)
		{
			printfDx("������");
			ChangeAnim(anim::kGuard);
			m_isHitKey = true;
			m_isGuard = true;
			m_isPunch = false;
		}
		else if (!CheckHitKey(KEY_INPUT_P) && m_isGuard)
		{
			//�K�[�h����߂鏈��������
			ChangeAnim(anim::kIdle);
			m_isGuard = false;
		}
		if (!CheckHitKey(KEY_INPUT_O) && !CheckHitKey(KEY_INPUT_P))
		{
			m_isHitKey = false;
		}
	}

	m_animTime += m_animPlaySpeed;
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
		hitKind = player->OnDamage(m_isCounter);
		HitPunch(hitKind);
		SetDamagePos();
		player->SetDamagePos();
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

void Enemy::Draw()
{
	MV1DrawModel(m_model);
	DrawFormatString(300, 100, GetColor(255, 255, 255), "E%d", -m_damage);
}

CharacterBase::damageKind Enemy::OnDamage(bool counter)
{
	CharacterBase::damageKind ans;
	//�K�[�h���Ă�����
	if (m_isGuard)
	{
		m_damage += baseConstant::kGuardDamage;
		m_gapTime = baseConstant::kGuardGapTime;
		ans = damageKind::kGuard;
	}
	//�J�E���^�[�̃^�C�~���O
	else if (counter)
	{
		m_damage += baseConstant::kCounterDamage;
		m_gapTime = baseConstant::kHitGapTime;
		ChangeAnim(anim::kHitReaction);
		ans = damageKind::kCounter;
	}
	//���ʂɃq�b�g
	else
	{
		m_damage += baseConstant::kHitDamage;
		m_gapTime = baseConstant::kHitGapTime;
		ChangeAnim(anim::kHitReaction);
		ans = damageKind::kHit;
	}
	m_pos.x = baseConstant::kDamageLange * -m_damage + baseConstant::kEnemyLange;
	m_isPunch = false;
	m_punchTime = 0;
	return ans;
}

void Enemy::HitPunch(damageKind kind)
{
	if (kind == damageKind::kHit)
	{
		m_gapTime = baseConstant::kHitPunchGapTime;
		m_damage -= baseConstant::kHitDamage;
	}
	else if (kind == damageKind::kGuard)
	{
		m_gapTime = baseConstant::kGuardHitGapTime;
		m_damage -= baseConstant::kGuardDamage;
	}
	else if (kind == damageKind::kCounter)
	{
		m_gapTime = baseConstant::kHitGapTime;
		m_damage -= baseConstant::kCounterDamage;
	}
}

void Enemy::SetDamagePos()
{
	m_pos.x = baseConstant::kDamageLange * m_damage + baseConstant::kEnemyLange;
}
