#include "Obstruct.h"

Obstruct::Obstruct():
	m_groundPos(),
	m_spikesPos(),
	m_groundModel(-1),
	m_spikesModel(-1),
	m_domeModel(-1)
{
	m_groundModel = MV1LoadModel("data/model/Ground.mv1");
	m_spikesModel = MV1LoadModel("data/model/Spikes.mv1");
	m_domeModel = MV1LoadModel("data/model/dome.mv1");
}

Obstruct::~Obstruct()
{
	MV1DeleteModel(m_groundModel);
	MV1DeleteModel(m_spikesModel);
	MV1DeleteModel(m_domeModel);
}

void Obstruct::Init()
{
	//�v���C���[�̗����Ă���n�ʂ̕\��
	m_groundPos = VGet(0, -120, 0);
	MV1SetPosition(m_groundModel, m_groundPos);
	//��������ɂ���j�̕\��
	m_spikesPos = VGet(0, -1000, 0);
	MV1SetPosition(m_spikesModel, m_spikesPos);
	//�X�J�C�h�[���̍��W�ݒ�
	MV1SetPosition(m_domeModel, VGet(0, 0, 0));
	MV1SetScale(m_domeModel, VGet(20, 20, 20));
}

void Obstruct::Update()
{
}

void Obstruct::Draw()
{
	MV1DrawModel(m_groundModel);
	MV1DrawModel(m_spikesModel);
	MV1DrawModel(m_domeModel);
}
