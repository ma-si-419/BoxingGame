#pragma once
#include "CharacterBase.h"
class Input;
class Player : public CharacterBase
{
public:
	Player();
	~Player();

	void Init();
	void Update(std::shared_ptr<CharacterBase> enemy,Input input);
	void Draw();

	//�_���[�W��Ԃ�
	int GetDamage() { return m_damage; }
};

