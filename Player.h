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

	//パンチを受けた時の関数
	CharacterBase::damageKind OnDamage(bool counter);
	//パンチを当てた時の関数
	void HitPunch(damageKind kind);
	//ダメージを受けた時に座標修正する関数
	void SetDamagePos();
	//パンチの状態を返す
	bool GetPunchState() { return m_isPunch; }
};

