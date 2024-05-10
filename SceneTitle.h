#pragma once
#include "SceneBase.h"
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
	int m_logoHandle;//�^�C�g�����S�̃n���h��
	int m_charactermodel[2];//�L�����N�^�[�̃��f��
	int m_domemodel;//�X�J�C�h�[���̃n���h��

	std::shared_ptr<Camera> m_pCamera;

};