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
	//1P側と設定
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
	//動けるタイミングだった時
	if (!m_isGap && !m_isFinishGame)
	{
		//ガードボタンを押したとき
		if (input.IsPress("leftShoulder") && !m_isHitGuardKey)
		{
			ChangeAnim(anim::kGuard);
			m_isGuard = true;
			m_isHitGuardKey = true;
			m_isPunch = false;
		}
		//パンチボタンを押したとき
		if (input.IsTrigger("leftTrigger") && !m_isPunch)
		{
			ChangeAnim(anim::kPunch);
			m_isPunch = true;
			m_isGuard = false;
			//相手がパンチを打っている状態だったらパンチの速度をあげる
			m_isCounter = enemy->GetPunchState();
		}
		//ガードボタンが離されたときの処理
		if (!CheckHitKey(KEY_INPUT_X))
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
	PlayAnim();
	//パンチの処理
	if (m_isPunch)
	{
		//カウンターだった場合パンチが当たるまでのスピードを速める
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
	//試合が終わった時の処理
	if (m_isFinishGame)
	{
		//試合に負けていたら
		if (m_damage < -kFinishDamage)
		{
			//下に落ちていく処理を入れる
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
