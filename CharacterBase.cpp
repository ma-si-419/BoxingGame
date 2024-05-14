#include "CharacterBase.h"
namespace
{
	//�ҋ@���̃��[�V����
	constexpr int kIdleAnimNumber = 3;
	//�K�[�h���̃��[�V����
	constexpr int kGuardAnimNumber = 1;
	//�p���`���̃��[�V����
	constexpr int kPunchAnimNumber = 10;
	//����ꂽ���̃��[�V����
	constexpr int kHitReactionAnimNumber = 2;
	//���������̃��[�V����
	constexpr int kWinReactionAnimNumber = 16;
	//���������̃��[�V����
	constexpr int kLoseReactionAnimNumber = 0;
	//�A�j���[�V�������ꂼ��̍Đ����x
	constexpr float kAnimPlaySpeed[6] = { 1.5f,2.0f,1.1f,1.0f,1.5f,2.0f };
}
CharacterBase::CharacterBase() :
	m_model(0),
	m_pos(),
	m_attachAnim(0),
	m_animTime(0),
	m_totalAnimTime(0),
	m_playAnim(),
	m_isGuard(false),
	m_isPunch(false),
	m_isHitPunchKey(false),
	m_isCounter(false),
	m_isPlayer(true),
	m_animPlaySpeed(0),
	m_damage(0),
	m_punchTime(0),
	m_isGap(false),
	m_gapTime(0),
	m_isFinishGame(false),
	m_isWin(false)
{
}

CharacterBase::~CharacterBase()
{
}

CharacterBase::damageKind CharacterBase::OnDamage(bool counter)
{
	damageKind ans;
	if (m_isPlayer)//1P���̏���
	{

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
	else//2P���̏���
	{
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
}

void CharacterBase::HitPunch(damageKind kind)
{
	//1P�����ǂ���
	if (m_isPlayer)
	{
		//�q�b�g
		if (kind == damageKind::kHit)
		{
			m_gapTime = baseConstant::kHitPunchGapTime;
			m_damage += baseConstant::kHitDamage;
		}
		//�K�[�h
		else if (kind == damageKind::kGuard)
		{
			m_gapTime = baseConstant::kGuardHitGapTime;
			m_damage += baseConstant::kGuardDamage;
		}
		//�J�E���^�[
		else if (kind == damageKind::kCounter)
		{
			m_gapTime = baseConstant::kHitGapTime;
			m_damage += baseConstant::kCounterDamage;
		}
	}
	else
	{
		//�q�b�g
		if (kind == damageKind::kHit)
		{
			m_gapTime = baseConstant::kHitPunchGapTime;
			m_damage -= baseConstant::kHitDamage;
		}
		//�K�[�h
		else if (kind == damageKind::kGuard)
		{
			m_gapTime = baseConstant::kGuardHitGapTime;
			m_damage -= baseConstant::kGuardDamage;
		}
		//�J�E���^�[
		else if (kind == damageKind::kCounter)
		{
			m_gapTime = baseConstant::kHitGapTime;
			m_damage -= baseConstant::kCounterDamage;
		}
	}
}

void CharacterBase::SetDamagePos()
{
	//1P�����ǂ���
	if (m_isPlayer)
	{
		m_pos.x = baseConstant::kDamageLange * m_damage - baseConstant::kEnemyLange;
	}
	else
	{
		m_pos.x = baseConstant::kDamageLange * m_damage + baseConstant::kEnemyLange;
	}
}

void CharacterBase::SetFinish(bool player)
{
	//1P�����ǂ���
	if (m_isPlayer)
	{
		m_isWin = player;
	}
	else
	{
		m_isWin = !player;
	}

	if (m_isWin && m_isPlayer == player)
	{
		//���ʂ���������
		MV1SetRotationXYZ(m_model, VGet(0, 0, 0));
		ChangeAnim(anim::kWinReaction);
	}
	else
	{
		ChangeAnim(anim::kLoseReaction);
	}


	m_isFinishGame = true;

}

void CharacterBase::ChangeAnim(anim nextAnim)
{
	int animNum = 0;
	//�A�j���̍Đ����x��ݒ�
	m_animPlaySpeed = kAnimPlaySpeed[static_cast<int>(nextAnim)];
	//�A�j���̍Đ����Ԃ����Z�b�g
	m_animTime = 0;
	//�O�̃A�j��������
	MV1DetachAnim(m_model, m_attachAnim);
	//�Đ����Ă���A�j����ۑ�����
	m_playAnim = nextAnim;
	if (nextAnim == anim::kIdle)
	{
		animNum = kIdleAnimNumber;
	}
	else if (nextAnim == anim::kGuard)
	{
		animNum = kGuardAnimNumber;
	}
	else if (nextAnim == anim::kPunch)
	{
		animNum = kPunchAnimNumber;
	}
	else if (nextAnim == anim::kHitReaction)
	{
		animNum = kHitReactionAnimNumber;
	}
	else if (nextAnim == anim::kWinReaction)
	{
		animNum = kWinReactionAnimNumber;
	}
	else if (nextAnim == anim::kLoseReaction)
	{
		animNum = kLoseReactionAnimNumber;
	}
	//�V�����A�j�����A�^�b�`����
	m_attachAnim = MV1AttachAnim(m_model, animNum);
	//�A�j���[�V�����̑��Đ����Ԃ�ݒ肷��
	m_totalAnimTime = MV1GetAnimTotalTime(m_model, animNum);
	if (nextAnim == anim::kGuard)
	{
		//�K�[�h�̓��[�V�����̓r���Ŏ~�߂邽�ߑ��Đ����Ԃ�ς���
		m_totalAnimTime = 7.0f;
	}
}
