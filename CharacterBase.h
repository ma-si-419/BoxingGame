#pragma once
#include "DxLib.h"
#include <memory>
class battleManager;
class CharacterBase
{
public:
	CharacterBase(const TCHAR* model);
	virtual ~CharacterBase() = 0;

	virtual void Init() = 0;
	virtual void Update(std::shared_ptr<battleManager> manager) = 0;
	virtual void Draw() = 0;

	//座標を設定する
	void SetPos(int pos) { m_pos.x = pos; }
	//行動できる状態か返す
	bool GetGap() { return m_isGap; }
	//防御しているかどうかを返す
	bool GetGuard() { return m_isGuard; }

protected:
	void ChangeAnim(int animNum);
	//表示位置
	VECTOR m_pos;
	//モデルハンドル
	int m_handle;
	//防御しているかどうか
	bool m_isGuard;
	//行動できない状態か
	bool m_isGap;
	//攻撃を受けたかどうか
	bool m_isHitPunch;
	//アニメーションの現在再生している時間
	float m_animTime;
	//アニメーションの合計時間
	float m_animTotalTime;
	//アタッチしているアニメーション
	int m_attachAnim;
	//2Pかどうか
	bool m_is2P;
};

