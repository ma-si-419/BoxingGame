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
	bool m_isFinish;//ゲームが終了したか

	int m_timer;//制限時間を表示する

	bool m_isWinPlayer;

	int m_winPlayerGraph;//プレイヤーが勝った時に表示する画像ハンドル
	int m_winEnemyGraph;//エネミーが勝った時に表示する画像ハンドル
};

