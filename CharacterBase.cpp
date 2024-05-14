#include "CharacterBase.h"
namespace
{
	//待機時のモーション
	constexpr int kIdleAnimNumber = 3;
	//ガード時のモーション
	constexpr int kGuardAnimNumber = 1;
	//パンチ時のモーション
	constexpr int kPunchAnimNumber = 10;
	//殴られた時のモーション
	constexpr int kHitReactionAnimNumber = 2;
	//勝った時のモーション
	constexpr int kWinReactionAnimNumber = 16;
	//負けた時のモーション
	constexpr int kLoseReactionAnimNumber = 0;
	//アニメーションそれぞれの再生速度
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
	if (m_isPlayer)//1P側の処理
	{

		//ガードしていたら
		if (m_isGuard)
		{
			m_damage -= baseConstant::kGuardDamage;
			m_gapTime = baseConstant::kGuardGapTime;
			ans = damageKind::kGuard;
		}
		//カウンターのタイミング
		else if (counter)
		{
			m_damage -= baseConstant::kCounterDamage;
			m_gapTime = baseConstant::kHitGapTime;
			ChangeAnim(anim::kHitReaction);
			ans = damageKind::kCounter;
		}
		//普通にヒット
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
	else//2P側の処理
	{
		//ガードしていたら
		if (m_isGuard)
		{
			m_damage += baseConstant::kGuardDamage;
			m_gapTime = baseConstant::kGuardGapTime;
			ans = damageKind::kGuard;
		}
		//カウンターのタイミング
		else if (counter)
		{
			m_damage += baseConstant::kCounterDamage;
			m_gapTime = baseConstant::kHitGapTime;
			ChangeAnim(anim::kHitReaction);
			ans = damageKind::kCounter;
		}
		//普通にヒット
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
	//1P側かどうか
	if (m_isPlayer)
	{
		//ヒット
		if (kind == damageKind::kHit)
		{
			m_gapTime = baseConstant::kHitPunchGapTime;
			m_damage += baseConstant::kHitDamage;
		}
		//ガード
		else if (kind == damageKind::kGuard)
		{
			m_gapTime = baseConstant::kGuardHitGapTime;
			m_damage += baseConstant::kGuardDamage;
		}
		//カウンター
		else if (kind == damageKind::kCounter)
		{
			m_gapTime = baseConstant::kHitGapTime;
			m_damage += baseConstant::kCounterDamage;
		}
	}
	else
	{
		//ヒット
		if (kind == damageKind::kHit)
		{
			m_gapTime = baseConstant::kHitPunchGapTime;
			m_damage -= baseConstant::kHitDamage;
		}
		//ガード
		else if (kind == damageKind::kGuard)
		{
			m_gapTime = baseConstant::kGuardHitGapTime;
			m_damage -= baseConstant::kGuardDamage;
		}
		//カウンター
		else if (kind == damageKind::kCounter)
		{
			m_gapTime = baseConstant::kHitGapTime;
			m_damage -= baseConstant::kCounterDamage;
		}
	}
}

void CharacterBase::SetDamagePos()
{
	//1P側かどうか
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
	//1P側かどうか
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
		//正面を向かせる
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
	//アニメの再生速度を設定
	m_animPlaySpeed = kAnimPlaySpeed[static_cast<int>(nextAnim)];
	//アニメの再生時間をリセット
	m_animTime = 0;
	//前のアニメをけす
	MV1DetachAnim(m_model, m_attachAnim);
	//再生しているアニメを保存する
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
	//新しいアニメをアタッチする
	m_attachAnim = MV1AttachAnim(m_model, animNum);
	//アニメーションの総再生時間を設定する
	m_totalAnimTime = MV1GetAnimTotalTime(m_model, animNum);
	if (nextAnim == anim::kGuard)
	{
		//ガードはモーションの途中で止めるため総再生時間を変える
		m_totalAnimTime = 7.0f;
	}
}
