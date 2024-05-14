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

	//ƒ_ƒ[ƒW‚ğ•Ô‚·
	int GetDamage() { return m_damage; }
};

