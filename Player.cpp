#include "Player.h"
#include "battleManager.h"

Player::Player() :
	CharacterBase("data/model/Player.mv1")
{
}

Player::~Player()
{
	MV1DeleteModel(m_handle);
}

void Player::Init()
{
	m_pos = VGet(100, 100,0);
}

void Player::Update(std::shared_ptr<battleManager> manager)
{
	if (CheckHitKey(KEY_INPUT_A))
	{
		manager->Attack1P();
	}
	if (m_is2P)
	{
		m_pos.x = -m_damage * 5;
	}
	else
	{
		m_pos.x = m_damage * 5;
	}
	MV1SetPosition(m_handle, m_pos);
}

void Player::Draw()
{
	MV1DrawModel(m_handle);
}

