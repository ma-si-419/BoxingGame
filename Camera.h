#pragma once
#include "DxLib.h"
class Camera
{
public:
	Camera();
	~Camera();

	void Update();

	//勝利時の演出を入れる
	void SetWinner(VECTOR pos);
private:
	VECTOR m_pos;
	
	VECTOR m_targetPos;
	VECTOR m_moveVec;
	bool m_isFinish;
};

