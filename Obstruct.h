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
	int m_groundModel;
	int m_spikesModel;
	int m_domeModel;
	VECTOR m_groundPos;
	VECTOR m_spikesPos;
};

