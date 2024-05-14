#pragma once
#include "SceneBase.h"
#include <memory>

class Player;
class Enemy;
class Camera;
class Obstruct;
class Ui;
class SceneGame : public SceneBase
{
public:
	SceneGame(SceneManager& sceneManager, DataManager& dataManager);
	~SceneGame();
	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//�I������
	void End();
	//�������������܂������ɌĂԊ֐�
	void FinishGame(bool player);
private:

	bool m_isFinish;//�Q�[�����I���������ǂ���

	int m_timer;//��������

	int m_timeCount;//���Ԃ𐔂���Ƃ��Ɏg�p

	//�|�C���^
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Obstruct> m_pObstruct;
	std::shared_ptr<Ui> m_pUi;
};

