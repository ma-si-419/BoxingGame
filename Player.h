#pragma once
#include "CharacterBase.h"

class Player : public CharacterBase
{
public:
	Player();
	~Player();

	void Init();
	void Update(std::shared_ptr<CharacterBase> enemy);
	void Draw();

	//ダメージを返す
	int GetDamage() { return m_damage; }
};

