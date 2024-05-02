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
	virtual void OnDamage(damageKind kind,bool player) = 0;
	//�_���[�W���󂯂����ɍ��W�C������֐�
	virtual void SetDamagePos(bool player) = 0;
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
	//�v���C���[�P���ǂ���
	bool m_isPlayer;
	//���ǂ̂��炢�_���[�W���󂯂Ă��邩��\��
	int m_damage;
};

