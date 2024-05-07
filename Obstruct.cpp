#include "Obstruct.h"

Obstruct::Obstruct():
	m_groundPos(),
	m_spikesPos(),
	m_groundHandle(-1),
	m_spikesHandle(-1),
	m_domeHandle(-1)
{
	m_groundHandle = MV1LoadModel("data/model/Ground.mv1");
	m_spikesHandle = MV1LoadModel("data/model/Spikes.mv1");
	m_domeHandle = MV1LoadModel("data/model/dome.mv1");
}

Obstruct::~Obstruct()
{
}

void Obstruct::Init()
{
	//プレイヤーの立っている地面の表示
	m_groundPos = VGet(0, -120, 0);
	MV1SetPosition(m_groundHandle, m_groundPos);
	//落ちた先にある針の表示
	m_spikesPos = VGet(0, -1000, 0);
	MV1SetPosition(m_spikesHandle, m_spikesPos);
	//スカイドームの座標設定
	MV1SetPosition(m_domeHandle, VGet(0, 0, 0));
	MV1SetScale(m_domeHandle, VGet(20, 20, 20));
}

void Obstruct::Update()
{
}

void Obstruct::Draw()
{
	MV1DrawModel(m_groundHandle);
	MV1DrawModel(m_spikesHandle);
	MV1DrawModel(m_domeHandle);
}
