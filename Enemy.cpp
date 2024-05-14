#include "Enemy.h"
Enemy::Enemy()
{
	m_model = MV1LoadModel("data/model/Player.mv1");
	ChangeAnim(anim::kIdle);

	m_pos = VGet(baseConstant::kEnemyLange, 0, 0);
	MV1SetRotationXYZ(m_model, VGet(0, static_cast<float> ((DX_PI_F / 180) * 90), 0));
	//2P側だと設定
	m_isPlayer = false;
}
Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update(std::shared_ptr<CharacterBase> player)
{
	//動けるタイミングだった時
	if (!m_isGap && !m_isFinishGame)
	{
		//ガードボタンを押したとき
		if (CheckHitKey(KEY_INPUT_P) && !m_isHitGuardKey)
		{
			ChangeAnim(anim::kGuard);
			m_isGuard = true;
			m_isHitGuardKey = true;
			m_isPunch = false;
		}
		//パンチボタンを押したとき
		if (CheckHitKey(KEY_INPUT_O) && !m_isHitPunchKey && !m_isPunch)
		{
			ChangeAnim(anim::kPunch);
			m_isPunch = true;
			m_isGuard = false;
			m_isHitPunchKey = true;
			//相手がパンチを打っている状態だったらパンチの速度をあげる
			m_isCounter = player->GetPunchState();
		}
		//パンチボタンが話されたときの処理
		if (!CheckHitKey(KEY_INPUT_O))
		{
			m_isHitPunchKey = false;
		}
		//ガードボタンが離されたときの処理
		if (!CheckHitKey(KEY_INPUT_P))
		{
			m_isHitGuardKey = false;
			//ガードしていたら
			if (m_isGuard)
			{
				//ガードをやめる処理を入れる
				ChangeAnim(anim::kIdle);
				m_isGuard = false;
			}
		}

	}
	//アニメーション処理
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


	//硬直管理
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
