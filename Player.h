#pragma once
#include "CharacterBase.h"
#include <memory>
class battleManager;
class Player : public CharacterBase
{
public:
	Player();
	~Player();

	void Init();
	void Update(std::shared_ptr<battleManager> manager);
	void Draw();

private:

	bool m_isPlayer1HitKey;
};

