#include "Player.h"
#include "battleManager.h"

Player::Player() :
	CharacterBase("data/model/Player.mv1"),
	m_isPlayer1HitKey()
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
	if (CheckHitKey(KEY_INPUT_A) && !m_isPlayer1HitKey)
	{
		manager->PlayerAttack(true);
		m_isPlayer1HitKey = true;
	}
	else if(!CheckHitKey(KEY_INPUT_A))
	{
		m_isPlayer1HitKey = false;
	}
	MV1SetPosition(m_handle, m_pos);
}

void Player::Draw()
{
	MV1DrawModel(m_handle);
}


