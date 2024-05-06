#pragma once
#include "DxLib.h"
#include <memory>
class CharacterBase
{
protected:
	enum class damageKind
	{
		kHit,
		kGuard,
		kCounter
	};
	enum class anim
	{
		kIdle,
		kGuard,
		kPunch,
		kHitReaction
	};
public:
	CharacterBase();
	virtual ~CharacterBase();

	virtual void Init() = 0;
	virtual void Update(std::shared_ptr<CharacterBase> player) = 0;
	virtual void Draw() = 0;

	//�p���`���󂯂����̊֐�
	virtual damageKind OnDamage(bool counter) = 0;
	//�p���`�𓖂Ă����̊֐�
	virtual void HitPunch(damageKind kind) = 0;
	//�_���[�W���󂯂����ɍ��W�C������֐�
	virtual void SetDamagePos() = 0;
	//���p���`��ł��Ă��邩�ǂ���
	virtual bool GetPunchState() = 0;
protected:	
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
	//�K�[�h���Ă��邩�ǂ���
	bool m_isGuard;
	//�p���`���Ă��邩�ǂ���
	bool m_isPunch;
	//�p���`���n�߂Ăǂ̂��炢�̎��Ԃ���������
	int m_punchTime;
	//�v���C���[�P���ǂ���
	bool m_isPlayer;
	//���ǂ̂��炢�_���[�W���󂯂Ă��邩��\��
	int m_damage;
	//�J�E���^�[���ǂ���
	bool m_isCounter;
};

