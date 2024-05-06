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

	//�p���`���󂯂����̊֐�
	damageKind OnDamage(bool counter);
	//�p���`�𓖂Ă����̊֐�
	void HitPunch(damageKind kind);
	//�_���[�W���󂯂����ɍ��W�C������֐�
	void SetDamagePos();
	//�p���`�̏�Ԃ�Ԃ�
	bool GetPunchState() { return m_isPunch; }
};

