#pragma once
#include <memory>

class CharacterBase;
class battleManager
{
public:

	battleManager(std::shared_ptr<CharacterBase> player1, std::shared_ptr<CharacterBase> player2);

	~battleManager();

	void Init();
	void Update();

	void PlayerAttack(bool player1);


private:
	enum class damageKind
	{
		kCounter,
		kHit,
		kGuard
	};
	void HitPunch(bool player1, damageKind kind);

	std::shared_ptr<CharacterBase> m_pPlayer[2];

	//��l�̃_���[�W�󋵂�����킷
	int m_damageState;
	//�v���C���[1���U�����n�߂����ǂ���
	bool m_isAttackPlayer1;
	//�v���C���[2���U�����n�߂����ǂ���
	bool m_isAttackPlayer2;
	//�p���`��ł��Ă���̎��Ԃ��v��
	int m_player1PunchTimeCount;
	int m_player2PunchTimeCount;
};

