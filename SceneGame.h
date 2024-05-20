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
	/// <summary>
	/// ����������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	void End();
	/// <summary>
	/// �������������܂������ɌĂԊ֐�
	/// </summary>
	/// <param name="player">1P�������������ǂ���</param>
	void FinishGame(bool player);
	/// <summary>
	/// ���������ɂȂ������ɌĂԊ֐�
	/// </summary>
	void DrawGame();
private:

	bool m_isFinish;//�Q�[�����I���������ǂ���

	bool m_isDraw;//�����������ǂ���

	int m_timer;//��������

	int m_timeCount;//���Ԃ𐔂���Ƃ��Ɏg�p

	/*�T�E���h�֌W*/
	int m_startGameSound;//�������n�܂������̌��ʉ�
	int m_drawSound;//���������ɂȂ������̌��ʉ�
	int m_winGameSound;//�ǂ��炩�����������̌��ʉ�
	int m_finishGameSound;//�������I��������̌��ʉ�
	int m_bgmSound;//BGM

	//�|�C���^
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Obstruct> m_pObstruct;
	std::shared_ptr<Ui> m_pUi;
};

