#include "Obstruct.h"

Obstruct::Obstruct():
	m_groundPos(),
	m_spikesPos(),
	m_groundmodel(-1),
	m_spikesmodel(-1),
	m_domeModel(-1)
{
	m_groundmodel = MV1LoadModel("data/model/Ground.mv1");
	m_spikesmodel = MV1LoadModel("data/model/Spikes.mv1");
	m_domeModel = MV1LoadModel("data/model/dome.mv1");
}

Obstruct::~Obstruct()
{
}

void Obstruct::Init()
{
	//プレイヤーの立っている地面の表示
	m_groundPos = VGet(0, -120, 0);
	MV1SetPosition(m_groundmodel, m_groundPos);
	//落ちた先にある針の表示
	m_spikesPos = VGet(0, -1000, 0);
	MV1SetPosition(m_spikesmodel, m_spikesPos);
	//スカイドームの座標設定
	MV1SetPosition(m_domeModel, VGet(0, 0, 0));
	MV1SetScale(m_domeModel, VGet(20, 20, 20));
}

void Obstruct::Update()
{
}

void Obstruct::Draw()
{
	MV1DrawModel(m_groundmodel);
	MV1DrawModel(m_spikesmodel);
	MV1DrawModel(m_domeModel);
}
