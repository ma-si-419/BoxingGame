#pragma once
#include "DxLib.h"
class CharacterBase
{
public:
	CharacterBase();
	virtual ~CharacterBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	enum class anim
	{
		kIdle,
		kGuard,
		kPunch,
		kHitReaction
	};
	//�A�j���[�V������ύX����
	void ChangeAnim(anim nextAnim);
	//�O���t�B�b�N
	int m_handle;
	//�A�j���[�V������ۑ�����
	int m_attachAnim;
	//���Đ����Ă���A�j����ۑ�����
	anim m_playAnim;
	//�A�j���[�V�����̍Đ����x
	float m_animPlaySpeed;
	//�A�j���[�V�����̍Đ����Ă��鎞��
	float m_animTime;
	//�A�j���[�V�����̑��Đ�����
	float m_totalAnimTime;
	//�\�����W
	VECTOR m_pos;
	//�p���`�̍��W
	VECTOR m_punchPos;
	//�{�^����O�̃t���[���ŉ��������ǂ���
	bool m_isHitKey;
};

