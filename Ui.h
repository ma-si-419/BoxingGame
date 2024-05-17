#pragma once
#include <map>
#include "DxLib.h"
class Ui
{
public:
	Ui();
	~Ui();

	void Init();
	void Update();
	void Draw();

	/// <summary>
	/// �^�C�}�[��\������
	/// </summary>
	void DrawTimer();

	/// <summary>
	/// �������I���������ɌĂ�
	/// </summary>
	/// <param name="player">����������1P�����ǂ���</param>
	void SetFinish(bool player) { m_isWinPlayer = player; m_isFinish = true; }

	/// <summary>
	/// ���������������ŏI��������ɌĂ�
	/// </summary>
	void SetDraw() { m_isDraw = true; }

	/// <summary>
	/// �Q�[���V�[�����猻�݉��b���擾����
	/// </summary>
	/// <param name="time">�������Ԃ������b��</param>
	void SetTimer(int time) { m_timer = time; }

	/// <summary>
	/// �����I�����̉��o���I������̂��擾����
	/// </summary>
	/// <returns>�������I���������ǂ���</returns>
	bool GetFinishStaging() { return !m_isStagingGraphShake; }

private:
	bool m_isFinish;//�Q�[�����I��������

	int m_timer;//�������Ԃ�\������

	bool m_isWinPlayer;//�ǂ���̃v���C���[����������

	bool m_isDraw;//�����������ǂ���

	/*�������������܂����Ƃ��ɕ\������摜�n���h��*/
	int m_winPlayerGraph;
	int m_winEnemyGraph;
	int m_drawGraph;

	/*�����I�����̉摜�֌W*/
	double m_stagingGraphScale;//�T�C�Y
	bool m_isStagingGraphShake;//�h�炵�Ă��邩�ǂ���
	VECTOR m_stagingGraphPos;//�\�����W
	int m_shakeTime;//�h�炵������

	std::map<char, int> m_timerMap;//0~9�܂ł̐����������Ă���
};

