#include "Player.h"
namespace
{
	constexpr float kPunchMaxLange = 16.0f;
	//ヒットした時のダメージ
	constexpr int kHitDamage = 5;
	//ガードした時のダメージ
	constexpr int kGuardDamage = 2;
	//カウンターされた時のダメージ
	constexpr int kCounterDamage = 12;
	//基本的な相手との距離
	constexpr int kEnemyLange = 125;
	//1ダメージごとに動く距離
	constexpr float kDamageLange = 10;
}
Player::Player(bool player)
{
	m_isPlayer = player;
	m_handle = MV1LoadModel("data/model/Player.mv1");
	ChangeAnim(anim::kIdle);
	if (player)
	{
		m_pos = VGet(-kEnemyLange, 0, 0);
		MV1SetRotationXYZ(m_handle, VGet(0, static_cast<float> ((DX_PI_F / 180) * 270), 0));
	}
	else
	{
		m_pos = VGet(kEnemyLange, 0, 0);
		MV1SetRotationXYZ(m_handle, VGet(0, static_cast<float> ((DX_PI_F / 180) * 90), 0));
	}
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update(std::shared_ptr<CharacterBase> enemy)
{
	if (m_isPlayer)
	{
		//パンチボタンを押したとき
		if (CheckHitKey(KEY_INPUT_Z) && !m_isHitKey && !m_isPunch)
		{
			ChangeAnim(anim::kPunch);
			m_isPunch = true;
			m_isHitKey = true;
			m_damage += kHitDamage;
			enemy->OnDamage(CharacterBase::damageKind::kHit, m_isPlayer);
			SetDamagePos(m_isPlayer);
			enemy->SetDamagePos(!m_isPlayer);
		}
		//ガードボタンを押したとき
		if (CheckHitKey(KEY_INPUT_X) && !m_isHitKey)
		{
			printfDx("押した");
			ChangeAnim(anim::kGuard);
			m_isHitKey = true;
			m_isGuard = true;
			m_isPunch = false;
		}
		//ガードボタンを離したとき
		else if (!CheckHitKey(KEY_INPUT_X) && m_isGuard)
		{
			//ガードをやめる処理を入れる
			ChangeAnim(anim::kIdle);
			m_isGuard = false;
		}
		//パンチボタンとガードボタンを離した時
		if (!CheckHitKey(KEY_INPUT_Z) && !CheckHitKey(KEY_INPUT_X))
		{
			m_isHitKey = false;
		}

		m_animTime += m_animPlaySpeed;
		if (m_animTime > m_totalAnimTime)
		{
			m_animTime = 0;
			if (m_playAnim == anim::kPunch)
			{
				m_isPunch = false;
				ChangeAnim(anim::kIdle);
			}
			else if (m_playAnim == anim::kGuard)
			{
				m_animTime = m_totalAnimTime;
			}
		}
	}
	else
	{
		if (CheckHitKey(KEY_INPUT_O) && !m_isHitKey && !m_isPunch)
		{
			ChangeAnim(anim::kPunch);
			m_isPunch = true;
			m_isHitKey = true;
			m_damage -= kHitDamage;
			enemy->OnDamage(CharacterBase::damageKind::kHit, m_isPlayer);
			SetDamagePos(m_isPlayer);
			enemy->SetDamagePos(!m_isPlayer);
		}
		if (CheckHitKey(KEY_INPUT_P) && !m_isHitKey)
		{
			printfDx("押した");
			ChangeAnim(anim::kGuard);
			m_isHitKey = true;
			m_isGuard = true;
			m_isPunch = false;
		}
		else if (!CheckHitKey(KEY_INPUT_P) && m_isGuard)
		{
			//ガードをやめる処理を入れる
			ChangeAnim(anim::kIdle);
			m_isGuard = false;
		}
		if (!CheckHitKey(KEY_INPUT_O) && !CheckHitKey(KEY_INPUT_P))
		{
			m_isHitKey = false;
		}

		m_animTime += m_animPlaySpeed;
		if (m_animTime > m_totalAnimTime)
		{
			m_animTime = 0;
			if (m_playAnim == anim::kPunch)
			{
				m_isPunch = false;
				ChangeAnim(anim::kIdle);
			}
			else if (m_playAnim == anim::kGuard)
			{
				m_animTime = m_totalAnimTime;
			}
		}
	}
	MV1SetAttachAnimTime(m_handle, m_attachAnim, m_animTime);
	MV1SetPosition(m_handle, m_pos);
}

void Player::Draw()
{
	MV1DrawModel(m_handle);
}

void Player::OnDamage(damageKind kind, bool player)
{
	if (player)
	{
		if (kind == damageKind::kHit)
		{
			m_damage += kHitDamage;
		}
		else if (kind == damageKind::kGuard)
		{
			m_damage += kGuardDamage;
		}
		else if (kind == damageKind::kCounter)
		{
			m_damage += kCounterDamage;
		}
		m_pos.x = kDamageLange * m_damage + kEnemyLange;
	}
	else
	{
		if (kind == damageKind::kHit)
		{
			m_damage -= kHitDamage;
		}
		else if (kind == damageKind::kGuard)
		{
			m_damage -= kGuardDamage;
		}
		else if (kind == damageKind::kCounter)
		{
			m_damage -= kCounterDamage;
		}
		m_pos.x = kDamageLange * m_damage - kEnemyLange;
	}
}

void Player::SetDamagePos(bool player)
{
	if(player)
	{
		m_pos.x = kDamageLange * m_damage - kEnemyLange;
	}
	else
	{
		m_pos.x = kDamageLange * m_damage + kEnemyLange;
	}
}
