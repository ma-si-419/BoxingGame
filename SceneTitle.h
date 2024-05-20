#pragma once
#include "SceneBase.h"
#include "DxLib.h"
#include <memory>
class Camera;
class SceneTitle : public SceneBase
{
public:
	SceneTitle(SceneManager& sceneManager, DataManager& dataManager);
	~SceneTitle();
	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//�I������
	void End();
private:
	enum class Command
	{
		kStart,
		kEnd
	};
	//�L�����N�^�[�̏���������
	void InitChar();
	int m_logoHandle;//�^�C�g�����S�̃n���h��
	int m_characterModel[2];//�L�����N�^�[�̃��f��
	int m_domeModel;//�X�J�C�h�[���̃n���h��
	int m_fingerHandle;//�w�̉摜�n���h��
	VECTOR m_fingerPos;//�w�̍��W

	bool m_isHitKey;//�O�̃t���[���ŃG���^�[�L�[�������Ă�����

	float m_fingerShake;//�w�̗h�炷���W

	Command m_selectCommand;//�I��ł��鍀��

	std::shared_ptr<Camera> m_pCamera;//�J�����̃|�C���g

	int m_bgmSound;//BGM

};