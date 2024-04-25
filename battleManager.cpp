#include "battleManager.h"
#include "CharacterBase.h"

namespace
{
	//�J�E���^�[�q�b�g���̃_���[�W
	constexpr int kCounterHitDamage = 12;
	//�K�[�h�����ɉ���ꂽ�Ƃ��̃_���[�W
	constexpr int kHitDamage = 5;
	//�K�[�h�������̃_���[�W
	constexpr int kGuardDamage = 2;
	//�G�Ƀp���`��������܂ł̎���
	constexpr int kHitTime = 20;
	//�p���`���J�E���^�[�ɂȂ鎞��
	constexpr int kCounterTime = 15;
	//�p���`�����ł��ɂȂ鎞��
	constexpr int ktradingTime = 10;
}
battleManager::battleManager(std::shared_ptr<CharacterBase> player1, std::shared_ptr<CharacterBase> player2):
	m_isAttackPlayer1(false),
	m_isAttackPlayer2(false),
	m_player1PunchTimeCount(0),
	m_player2PunchTimeCount(0),
	m_damageState(0)
{
	m_pPlayer[0] = player1;
	m_pPlayer[1] = player2;
}

battleManager::~battleManager()
{
}

void battleManager::Init()
{
}

void battleManager::Update()
{
	if (m_isAttackPlayer1)
	{
		m_player1PunchTimeCount--;
	}
	if (m_isAttackPlayer2)
	{
		m_player2PunchTimeCount--;
	}
	if (m_player1PunchTimeCount <= 0)
	{
		if (m_pPlayer[1]->GetGuard())
		{
			HitPunch(true, damageKind::kGuard);
			m_isAttackPlayer1 = false;
			m_player1PunchTimeCount = kHitTime;
		}
		else
		{
			HitPunch(true, damageKind::kHit);
			m_isAttackPlayer1 = false;
			m_player1PunchTimeCount = kHitTime;
		}
		
	}

}

void battleManager::PlayerAttack(bool player1)
{
	if (player1)
	{
		m_isAttackPlayer1 = true;
		m_player1PunchTimeCount = kHitTime;
		if (m_player2PunchTimeCount > kCounterTime)
		{
			HitPunch(player1, damageKind::kCounter);
			m_isAttackPlayer1 = false;
			m_player1PunchTimeCount = 0;
		}
		else if (m_player2PunchTimeCount > ktradingTime)
		{
			HitPunch(player1, damageKind::kHit);
			HitPunch(!player1, damageKind::kHit);
			m_isAttackPlayer1 = false;
			m_player1PunchTimeCount = 0;
		}
		else if (m_player2PunchTimeCount >= kHitTime)
		{
			HitPunch(player1, damageKind::kHit);
			m_isAttackPlayer1 = false;
			m_player1PunchTimeCount = 0;
		}
	}
	else
	{
		m_isAttackPlayer2 = true;
		m_player2PunchTimeCount = kHitTime;
		if (m_player1PunchTimeCount > kCounterTime)
		{
			HitPunch(!player1, damageKind::kCounter);
			m_isAttackPlayer2 = false;
			m_player2PunchTimeCount = 0;
		}
		else if (m_player1PunchTimeCount > ktradingTime)
		{
			HitPunch(player1, damageKind::kHit);
			HitPunch(!player1, damageKind::kHit);
			m_isAttackPlayer2 = false;
			m_player2PunchTimeCount = 0;
		}
		else if (m_player1PunchTimeCount >= kHitTime)
		{
			HitPunch(player1, damageKind::kHit);
			m_isAttackPlayer2 = false;
			m_player2PunchTimeCount = 0;
		}
	}
	printfDx("punch");
}

void battleManager::HitPunch(bool player1, damageKind kind)
{
	if (player1)
	{
		switch (kind)
		{
		case battleManager::damageKind::kCounter:
			m_damageState += kCounterHitDamage;
			printfDx("Counter");
			break;
		case battleManager::damageKind::kHit:
			m_damageState += kHitDamage;
			printfDx("Hit");
			break;
		case battleManager::damageKind::kGuard:
			m_damageState += kGuardDamage;
			printfDx("Guard");
			break;
		default:
			break;
		}
	}
	else
	{
		switch (kind)
		{
		case battleManager::damageKind::kCounter:
			m_damageState -= kCounterHitDamage;
			printfDx("Counter");
			break;
		case battleManager::damageKind::kHit:
			m_damageState -= kHitDamage;
			printfDx("Hit");
			break;
		case battleManager::damageKind::kGuard:
			m_damageState -= kGuardDamage;
			printfDx("Guard");
			break;
		default:
			break;
		}
	}
}
