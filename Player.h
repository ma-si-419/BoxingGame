#pragma once
#include "CharacterBase.h"
class Player : public CharacterBase
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();

};

