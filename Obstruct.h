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
	int m_groundmodel;
	int m_spikesmodel;
	int m_domemodel;
	VECTOR m_groundPos;
	VECTOR m_spikesPos;
};

