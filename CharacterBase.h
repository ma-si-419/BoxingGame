#pragma once
#include "DxLib.h"
class CharacterBase
{
public:
	CharacterBase();
	virtual ~CharacterBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	enum class anim
	{
		kIdle,
		kGuard,
		kPunch,
		kHitReaction
	};
	//アニメーションを変更する
	void ChangeAnim(anim nextAnim);
	//グラフィック
	int m_handle;
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
};

