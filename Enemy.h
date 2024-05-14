#pragma once
#include "CharacterBase.h"
class Enemy : public CharacterBase
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update(std::shared_ptr<CharacterBase> player);
	void Draw();

};

