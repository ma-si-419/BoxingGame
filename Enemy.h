#pragma once
#include "CharacterBase.h"
class Input;
class Enemy : public CharacterBase
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update(std::shared_ptr<CharacterBase> player,Input input);
	void Draw();

};

