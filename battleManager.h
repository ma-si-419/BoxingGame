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

	//二人のダメージ状況をあらわす
	int m_damageState;
	//プレイヤー1が攻撃を始めたかどうか
	bool m_isAttackPlayer1;
	//プレイヤー2が攻撃を始めたかどうか
	bool m_isAttackPlayer2;
	//パンチを打ってからの時間を計測
	int m_player1PunchTimeCount;
	int m_player2PunchTimeCount;
};

