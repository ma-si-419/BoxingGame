#pragma once
#include "DxLib.h"
#include <memory>
class battleManager;
class CharacterBase
{
public:
	CharacterBase(const TCHAR* model);
	virtual ~CharacterBase() = 0;

	virtual void Init() = 0;
	virtual void Update(std::shared_ptr<battleManager> manager) = 0;
	virtual void Draw() = 0;

	//���W��ݒ肷��
	void SetPos(int pos) { m_pos.x = pos; }
	//�s���ł����Ԃ��Ԃ�
	bool GetGap() { return m_isGap; }
	//�h�䂵�Ă��邩�ǂ�����Ԃ�
	bool GetGuard() { return m_isGuard; }

protected:
	void ChangeAnim(int animNum);
	//�\���ʒu
	VECTOR m_pos;
	//���f���n���h��
	int m_handle;
	//�h�䂵�Ă��邩�ǂ���
	bool m_isGuard;
	//�s���ł��Ȃ���Ԃ�
	bool m_isGap;
	//�U�����󂯂����ǂ���
	bool m_isHitPunch;
	//�A�j���[�V�����̌��ݍĐ����Ă��鎞��
	float m_animTime;
	//�A�j���[�V�����̍��v����
	float m_animTotalTime;
	//�A�^�b�`���Ă���A�j���[�V����
	int m_attachAnim;
	//2P���ǂ���
	bool m_is2P;
};

