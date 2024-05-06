#include "Enemy.h"
namespace
{
	//パンチが当たるまでの時間
	constexpr int kPunchHitTime = 10;
	//カウンターを打ったときのパンチの速度
	constexpr int kCounterPunchSpeed = 3;
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
Enemy::Enemy()
{
	m_handle = MV1LoadModel("data/model/Player.mv1");
	ChangeAnim(anim::kIdle);

	m_pos = VGet(kEnemyLange, 0, 0);
	MV1SetRotationXYZ(m_handle, VGet(0, static_cast<float> ((DX_PI_F / 180) * 90), 0));
}
Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update(std::shared_ptr<CharacterBase> player)
{
	//パンチボタンを押したとき
	if (CheckHitKey(KEY_INPUT_O) && !m_isHitKey && !m_isPunch)
	{
		ChangeAnim(anim::kPunch);
		m_isPunch = true;
		m_isHitKey = true;
		//相手がパンチを打っている状態だったらパンチの速度をあげる
		m_isCounter = player->GetPunchState();
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
		if (m_playAnim == anim::kPunch || m_playAnim == anim::kHitReaction)
		{
			m_isPunch = false;
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
			m_punchTime += kCounterPunchSpeed;
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
	if (m_punchTime > kPunchHitTime)
	{
		CharacterBase::damageKind hitKind;
		hitKind = player->OnDamage(m_isCounter);
		HitPunch(hitKind);
		SetDamagePos();
		player->SetDamagePos();
		m_isPunch = false;
		m_punchTime = 0;
	}

	MV1SetAttachAnimTime(m_handle, m_attachAnim, m_animTime);
	MV1SetPosition(m_handle, m_pos);
}

void Enemy::Draw()
{
	MV1DrawModel(m_handle);
	DrawFormatString(300, 100, GetColor(255, 255, 255), "E%d", -m_damage);
}

CharacterBase::damageKind Enemy::OnDamage(bool counter)
{
	CharacterBase::damageKind ans;
	//ガードしていたら
	if (m_isGuard)
	{
		m_damage += kGuardDamage;
		ans = damageKind::kGuard;
	}
	//カウンターのタイミング
	else if (counter)
	{
		m_damage += kCounterDamage;
		ChangeAnim(anim::kHitReaction);
		ans = damageKind::kCounter;
	}
	//普通にヒット
	else
	{
		m_damage += kHitDamage;
		ChangeAnim(anim::kHitReaction);
		ans = damageKind::kHit;
	}
	m_pos.x = kDamageLange * -m_damage + kEnemyLange;
	m_isPunch = false;
	m_punchTime = 0;
	return ans;
}

void Enemy::HitPunch(damageKind kind)
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
}

void Enemy::SetDamagePos()
{
	m_pos.x = kDamageLange * m_damage + kEnemyLange;
}
