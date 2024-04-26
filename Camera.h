#pragma once
#include "DxLib.h"
class Camera
{
public:
	Camera();
	~Camera();

	void Update();

private:
	VECTOR m_pos;
	VECTOR m_angle;
};

