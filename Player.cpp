#include "Player.h"

Player::Player()
{
	m_handle = MV1LoadModel("data/model/Player.mv1");
	ChangeAnim(anim::kIdle);
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_Z) && !m_isHitKey)
	{
		ChangeAnim(anim::kPunch);
		m_isHitKey = true;
	}
	else if (!CheckHitKey(KEY_INPUT_Z))
	{
		m_isHitKey = false;
	}
	if (CheckHitKey(KEY_INPUT_X) && !m_isHitKey)
	{
		ChangeAnim(anim::kGuard);
		m_isHitKey = true;
	}
	else if(CheckHitKey(KEY_INPUT_X))
	{
		//ƒK[ƒh‚ð‚â‚ß‚éˆ—‚ð“ü‚ê‚é
	}

	m_animTime += m_animPlaySpeed;
	if (m_animTime > m_totalAnimTime)
	{
		if (m_playAnim == anim::kPunch)
		{
			ChangeAnim(anim::kIdle);
		}
		else if (m_playAnim == anim::kGuard)
		{
			m_animTime = m_totalAnimTime;
		}
		m_animTime = 0;
	}
	MV1SetAttachAnimTime(m_handle, m_attachAnim, m_animTime);
	MV1SetPosition(m_handle, m_pos);
}

void Player::Draw()
{
	MV1DrawModel(m_handle);
}
