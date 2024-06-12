#pragma once
#include "DxLib.h"
#include <memory>
namespace baseConstant
{
	//パンチが当たるまでの時間
	constexpr int kPunchHitTime = 10;
	//カウンターを打ったときのパンチの速度
	constexpr int kCounterPunchSpeed = 3;
	//ヒットした時のダメージ
	constexpr int kHitDamage = 5;
	//ヒットした時の硬直
	constexpr int kHitPunchGapTime = 10;
	//殴られたときの硬直
	constexpr int kHitGapTime = 10;
	//ガードした時のダメージ
	constexpr int kGuardDamage = 2;
	//ガードした時の硬直
	constexpr int kGuardGapTime = 5;
	//ガードされたときの硬直
	constexpr int kGuardHitGapTime = 20;
	//カウンターされた時のダメージ
	constexpr int kCounterDamage = 12;
	//基本的な相手との距離
	constexpr int kEnemyLange = 125;
	//1ダメージごとに動く距離
	constexpr float kDamageLange = 10;
}
class Input;
class CharacterBase
{
protected:
	enum class damageKind
	{
		kPunchHit,
		kGuard,
		kCounterHit
	};
	enum class anim
	{
		kIdle,
		kGuard,
		kPunch,
		kCounter,
		kHitReaction,
		kWinReaction,
		kLoseReaction
	};

public:
	CharacterBase();
	virtual ~CharacterBase();

	virtual void Init() = 0;
	virtual void Update(std::shared_ptr<CharacterBase> player,Input input) = 0;
	virtual void Draw() = 0;

	//パンチを受けた時の関数
	virtual damageKind OnDamage(bool counter);
	//パンチを当てた時の関数
	virtual void HitPunch(damageKind kind);
	//ダメージを受けた時に座標修正する関数
	virtual void SetDamagePos();
	//ゲームが終了した時に呼ぶ関数
	virtual void SetFinish(bool player);
	//引き分けでゲームが終了した時に呼ぶ関数
	virtual void SetDraw();
	//今パンチを打っているかどうか
	virtual bool GetPunchState() { return m_isPunch; };
	//現在地を返す
	virtual VECTOR GetPos() { return m_pos; }
protected:
	/*アニメーション、モデル関係*/
	void ChangeAnim(anim nextAnim);	//アニメーションを変更する
	void PlayAnim();
	int m_model;	//グラフィック
	int m_attachAnim;	//アニメーションを保存する
	anim m_playAnim;	//今再生しているアニメを保存する
	float m_animPlaySpeed;	//アニメーションの再生速度
	float m_animTime;	//アニメーションの再生している時間
	float m_totalAnimTime;	//アニメーションの総再生時間
	VECTOR m_pos;	//表示座標

	/*操作制御*/
	bool m_isHitPunchKey;	//パンチボタンを前のフレームで押したか
	bool m_isHitGuardKey;	//ガードボタンを前のフレームで押したか
	bool m_isPlayer;	//プレイヤー１かどうか

	/*状態制御*/
	bool m_isGuard;	//ガードしているかどうか
	bool m_isPunch;	//パンチしているかどうか
	int m_punchTime;	//パンチを始めてどのくらいの時間がたったか
	int m_damage;	//今どのくらいダメージを受けているかを表す
	bool m_isCounter;	//カウンターかどうか
	bool m_isGap;	//動ける状態かどうか
	int m_gapTime;//動けなくなってから何秒か

	/*終了処理関係*/
	bool m_isFinishGame;//ゲームが終了したかどうか
	bool m_isWin;//勝ったかどうか
	bool m_isDraw;//引き分けかどうか

	/*音声関係*/
	int m_hitPunchSound;
	int m_hitCounterSound;
	int m_guardSound;
};

