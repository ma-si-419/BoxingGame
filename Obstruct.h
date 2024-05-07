#pragma once
#include "DxLib.h"
class Obstruct
{
public:
	Obstruct();
	~Obstruct();

	void Init();
	void Update();
	void Draw();
private:
	int m_groundHandle;
	int m_spikesHandle;
	int m_domeHandle;
	VECTOR m_groundPos;
	VECTOR m_spikesPos;
};

