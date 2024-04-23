#include "CharacterBase.h"

namespace
{
	constexpr int kIdleAnimNumber = 3;
}
CharacterBase::CharacterBase(const TCHAR* model) :
	m_pos(),
	m_damage(0),
	m_handle(-1),
	m_isGuard(false),
	m_isGap(false),
	m_animTime(0),
	m_animTotalTime(0),
	m_attachAnim(-1),
	m_is2P(false)
{
	// ‚R‚cƒ‚ƒfƒ‹‚Ì“Ç‚İ‚İ
	m_handle = MV1LoadModel(model);
	ChangeAnim(kIdleAnimNumber);
	if (m_handle < 0)
	{
		printfDx("ƒf[ƒ^“Ç‚İ‚İ‚É¸”s");
	}
}

CharacterBase::~CharacterBase()
{

}

void CharacterBase::Init()
{

}

void CharacterBase::Update()
{
}

void CharacterBase::Draw()
{
}

void CharacterBase::ChangeAnim(int animNum)
{
	MV1DetachAnim(m_handle, m_attachAnim);
	m_attachAnim = MV1AttachAnim(m_handle, animNum);
	m_animTime = 0;
	m_animTotalTime = MV1GetAnimTotalTime(m_handle, animNum);
}
