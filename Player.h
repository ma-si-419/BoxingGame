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

	//�p���`���󂯂����̊֐�
	void OnDamage(CharacterBase::damageKind kind,bool player);
	//�_���[�W���󂯂����ɍ��W�C������֐�
	void SetDamagePos(bool player);
};

