#pragma once
#include "DxLib.h"
#include <memory>
namespace baseConstant
{
	//パンチが当たるまでの時間
	constexpr int kPunchHitTime = 15;
	//カウンターを打ったときのパンチの速度
	constexpr int kCounterPunchSpeed = 3;
	//ヒットした時のダメージ
	constexpr int kHitDamage = 5;
	//ヒットした時の硬直
	constexpr int kHitPunchGapTime = 15;
	//殴られたときの硬直
	constexpr int kHitGapTime = 15;
	//ガードした時のダメージ
	constexpr int kGuardDamage = 2;
	//ガードした時の硬直
	constexpr int kGuardGapTime = 10;
	//ガードされたときの硬直
	constexpr int kGuardHitGapTime = 30;
	//カウンターされた時のダメージ
	constexpr int kCounterDamage = 12;
	//基本的な相手との距離
	constexpr int kEnemyLange = 125;
	//1ダメージごとに動く距離
	constexpr float kDamageLange = 10;
}
class CharacterBase
{
protected:
	enum class damageKind
	{
		kHit,
		kGuard,
		kCounter
	};
	enum class anim
	{
		kIdle,
		kGuard,
		kPunch,
		kHitReaction
	};
	
public:
	CharacterBase();
	virtual ~CharacterBase();

	virtual void Init() = 0;
	virtual void Update(std::shared_ptr<CharacterBase> player) = 0;
	virtual void Draw() = 0;

	//パンチを受けた時の関数
	virtual damageKind OnDamage(bool counter) = 0;
	//パンチを当てた時の関数
	virtual void HitPunch(damageKind kind) = 0;
	//ダメージを受けた時に座標修正する関数
	virtual void SetDamagePos() = 0;
	//今パンチを打っているかどうか
	virtual bool GetPunchState() = 0;
protected:	
	//アニメーションを変更する
	void ChangeAnim(anim nextAnim);
	//グラフィック
	int m_model;
	//アニメーションを保存する
	int m_attachAnim;
	//今再生しているアニメを保存する
	anim m_playAnim;
	//アニメーションの再生速度
	float m_animPlaySpeed;
	//アニメーションの再生している時間
	float m_animTime;
	//アニメーションの総再生時間
	float m_totalAnimTime;
	//表示座標
	VECTOR m_pos;
	//パンチの座標
	VECTOR m_punchPos;
	//ボタンを前のフレームで押したかどうか
	bool m_isHitKey;
	//ガードしているかどうか
	bool m_isGuard;
	//パンチしているかどうか
	bool m_isPunch;
	//パンチを始めてどのくらいの時間がたったか
	int m_punchTime;
	//プレイヤー１かどうか
	bool m_isPlayer;
	//今どのくらいダメージを受けているかを表す
	int m_damage;
	//カウンターかどうか
	bool m_isCounter;
	//動ける状態かどうか
	bool m_isGap;
	//動けなくなってから何秒か
	int m_gapTime;
};

