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
	//アニメーションそれぞれの再生速度
	constexpr float kAnimPlaySpeed[4] = { 1.5f,2.0f,1.1f,1.0f };
}
CharacterBase::CharacterBase() :
	m_handle(0),
	m_pos(),
	m_punchPos(),
	m_attachAnim(0),
	m_animTime(0),
	m_totalAnimTime(0),
	m_playAnim(),
	m_isGuard(false),
	m_isPunch(false),
	m_isHitKey(false),
	m_isCounter(false),
	m_isPlayer(true),
	m_animPlaySpeed(0),
	m_damage(0),
	m_punchTime(0),
	m_isGap(false),
	m_gapTime(0)
{
}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::ChangeAnim(anim nextAnim)
{
	int animNum = 0;
	//アニメの再生速度を設定
	m_animPlaySpeed = kAnimPlaySpeed[static_cast<int>(nextAnim)];
	//アニメの再生時間をリセット
	m_animTime = 0;
	//前のアニメをけす
	MV1DetachAnim(m_handle, m_attachAnim);
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
	//新しいアニメをアタッチする
	m_attachAnim = MV1AttachAnim(m_handle, animNum);
	//アニメーションの総再生時間を設定する
	m_totalAnimTime = MV1GetAnimTotalTime(m_handle, animNum);
	if (nextAnim == anim::kGuard)
	{
		//ガードはモーションの途中で止めるため総再生時間を変える
		m_totalAnimTime = 7.0f;
	}
}
