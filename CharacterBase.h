#pragma once
#include "DxLib.h"
#include <memory>
namespace baseConstant
{
	//�p���`��������܂ł̎���
	constexpr int kPunchHitTime = 10;
	//�J�E���^�[��ł����Ƃ��̃p���`�̑��x
	constexpr int kCounterPunchSpeed = 3;
	//�q�b�g�������̃_���[�W
	constexpr int kHitDamage = 5;
	//�q�b�g�������̍d��
	constexpr int kHitPunchGapTime = 10;
	//����ꂽ�Ƃ��̍d��
	constexpr int kHitGapTime = 10;
	//�K�[�h�������̃_���[�W
	constexpr int kGuardDamage = 2;
	//�K�[�h�������̍d��
	constexpr int kGuardGapTime = 5;
	//�K�[�h���ꂽ�Ƃ��̍d��
	constexpr int kGuardHitGapTime = 20;
	//�J�E���^�[���ꂽ���̃_���[�W
	constexpr int kCounterDamage = 12;
	//��{�I�ȑ���Ƃ̋���
	constexpr int kEnemyLange = 125;
	//1�_���[�W���Ƃɓ�������
	constexpr float kDamageLange = 10;
}
class Input;
class CharacterBase
{
protected:
	enum class damageKind
	{
		kPunchHit,
		kGuard,
		kCounterHit
	};
	enum class anim
	{
		kIdle,
		kGuard,
		kPunch,
		kCounter,
		kHitReaction,
		kWinReaction,
		kLoseReaction
	};

public:
	CharacterBase();
	virtual ~CharacterBase();

	virtual void Init() = 0;
	virtual void Update(std::shared_ptr<CharacterBase> player,Input input) = 0;
	virtual void Draw() = 0;

	//�p���`���󂯂����̊֐�
	virtual damageKind OnDamage(bool counter);
	//�p���`�𓖂Ă����̊֐�
	virtual void HitPunch(damageKind kind);
	//�_���[�W���󂯂����ɍ��W�C������֐�
	virtual void SetDamagePos();
	//�Q�[�����I���������ɌĂԊ֐�
	virtual void SetFinish(bool player);
	//���������ŃQ�[�����I���������ɌĂԊ֐�
	virtual void SetDraw();
	//���p���`��ł��Ă��邩�ǂ���
	virtual bool GetPunchState() { return m_isPunch; };
	//���ݒn��Ԃ�
	virtual VECTOR GetPos() { return m_pos; }
protected:
	/*�A�j���[�V�����A���f���֌W*/
	void ChangeAnim(anim nextAnim);	//�A�j���[�V������ύX����
	void PlayAnim();
	int m_model;	//�O���t�B�b�N
	int m_attachAnim;	//�A�j���[�V������ۑ�����
	anim m_playAnim;	//���Đ����Ă���A�j����ۑ�����
	float m_animPlaySpeed;	//�A�j���[�V�����̍Đ����x
	float m_animTime;	//�A�j���[�V�����̍Đ����Ă��鎞��
	float m_totalAnimTime;	//�A�j���[�V�����̑��Đ�����
	VECTOR m_pos;	//�\�����W

	/*���쐧��*/
	bool m_isHitPunchKey;	//�p���`�{�^����O�̃t���[���ŉ�������
	bool m_isHitGuardKey;	//�K�[�h�{�^����O�̃t���[���ŉ�������
	bool m_isPlayer;	//�v���C���[�P���ǂ���

	/*��Ԑ���*/
	bool m_isGuard;	//�K�[�h���Ă��邩�ǂ���
	bool m_isPunch;	//�p���`���Ă��邩�ǂ���
	int m_punchTime;	//�p���`���n�߂Ăǂ̂��炢�̎��Ԃ���������
	int m_damage;	//���ǂ̂��炢�_���[�W���󂯂Ă��邩��\��
	bool m_isCounter;	//�J�E���^�[���ǂ���
	bool m_isGap;	//�������Ԃ��ǂ���
	int m_gapTime;//�����Ȃ��Ȃ��Ă��牽�b��

	/*�I�������֌W*/
	bool m_isFinishGame;//�Q�[�����I���������ǂ���
	bool m_isWin;//���������ǂ���
	bool m_isDraw;//�����������ǂ���

	/*�����֌W*/
	int m_hitPunchSound;
	int m_hitCounterSound;
	int m_guardSound;
};

