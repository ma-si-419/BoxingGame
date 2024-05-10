#pragma once
#include "DxLib.h"
#include <memory>
namespace baseConstant
{
	//�p���`��������܂ł̎���
	constexpr int kPunchHitTime = 15;
	//�J�E���^�[��ł����Ƃ��̃p���`�̑��x
	constexpr int kCounterPunchSpeed = 3;
	//�q�b�g�������̃_���[�W
	constexpr int kHitDamage = 5;
	//�q�b�g�������̍d��
	constexpr int kHitPunchGapTime = 15;
	//����ꂽ�Ƃ��̍d��
	constexpr int kHitGapTime = 15;
	//�K�[�h�������̃_���[�W
	constexpr int kGuardDamage = 2;
	//�K�[�h�������̍d��
	constexpr int kGuardGapTime = 10;
	//�K�[�h���ꂽ�Ƃ��̍d��
	constexpr int kGuardHitGapTime = 30;
	//�J�E���^�[���ꂽ���̃_���[�W
	constexpr int kCounterDamage = 12;
	//��{�I�ȑ���Ƃ̋���
	constexpr int kEnemyLange = 125;
	//1�_���[�W���Ƃɓ�������
	constexpr float kDamageLange = 10;
}
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
	int m_model;
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
	//�������Ԃ��ǂ���
	bool m_isGap;
	//�����Ȃ��Ȃ��Ă��牽�b��
	int m_gapTime;
};

