#pragma once
class Ui
{
public:
	Ui();
	~Ui();

	void Init();
	void Update();
	void Draw();

	void SetFinish(bool player) { m_isWinPlayer = player; m_isFinish = true; }

	void SetTimer(int time) { m_timer = time; }
private:
	bool m_isFinish;//�Q�[�����I��������

	int m_timer;//�������Ԃ�\������

	bool m_isWinPlayer;

	int m_winPlayerGraph;//�v���C���[�����������ɕ\������摜�n���h��
	int m_winEnemyGraph;//�G�l�~�[�����������ɕ\������摜�n���h��
};

