#pragma once
#include "CharacterBase.h"

class Player : public CharacterBase
{
public:
	Player(bool player);
	~Player();

	void Init();
	void Update(std::shared_ptr<CharacterBase> enemy);
	void Draw();

	//パンチを受けた時の関数
	void OnDamage(CharacterBase::damageKind kind,bool player);
	//ダメージを受けた時に座標修正する関数
	void SetDamagePos(bool player);
};

