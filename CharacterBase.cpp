#include "CharacterBase.h"
namespace
{
	//�ҋ@���̃��[�V����
	constexpr int kIdleAnimNumber = 3;
	//�K�[�h���̃��[�V����
	constexpr int kGuardAnimNumber = 1;
	//�p���`���̃��[�V����
	constexpr int kPunchAnimNumber = 10;
	//����ꂽ���̃��[�V����
	constexpr int kHitReactionAnimNumber = 2;
	//�A�j���[�V�������ꂼ��̍Đ����x
	constexpr float kAnimPlaySpeed[4] = { 1.0f,1.0f,1.0f,1.0f };
}
CharacterBase::CharacterBase() :
	m_handle(0),
	m_pos(),
	m_punchPos(),
	m_attachAnim(0),
	m_animTime(0),
	m_totalAnimTime(0),
	m_playAnim()
{
}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::ChangeAnim(anim nextAnim)
{
	int animNum;
	//�A�j���̍Đ����x��ݒ�
	m_animPlaySpeed = kAnimPlaySpeed[static_cast<int>(nextAnim)];
	//�A�j���̍Đ����Ԃ����Z�b�g
	m_animTime = 0;
	//�O�̃A�j��������
	MV1DetachAnim(m_handle, m_attachAnim);
	//�Đ����Ă���A�j����ۑ�����
	m_playAnim = nextAnim;
	if (nextAnim == anim::kIdle)
	{
		animNum = kIdleAnimNumber;
	}
	else if (nextAnim == anim::kGuard)
	{
		animNum = kGuardAnimNumber;
		//�K�[�h�̓��[�V�����̓r���Ŏ~�߂邽�ߑ��Đ����Ԃ�ς���
		m_totalAnimTime = 18.5f;
	}
	else if (nextAnim == anim::kPunch)
	{
		animNum = kPunchAnimNumber;
	}
	else if (nextAnim == anim::kHitReaction)
	{
		animNum = kHitReactionAnimNumber;
	}
	//�V�����A�j�����A�^�b�`����
	m_attachAnim = MV1AttachAnim(m_handle, animNum);
	//�A�j���[�V�����̑��Đ����Ԃ�ݒ肷��
	m_totalAnimTime = MV1GetAnimTotalTime(m_handle, animNum);
}
