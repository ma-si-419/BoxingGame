#pragma once
#include "DxLib.h"
class Camera
{
public:
	Camera();
	~Camera();

	void Update();

	//Ÿ—˜‚Ì‰‰o‚ğ“ü‚ê‚é
	void SetWinner(VECTOR pos);
private:
	VECTOR m_pos;
	VECTOR m_angle;

	VECTOR m_targetPos;
	VECTOR m_moveVec;
	bool m_isFinish;
};

