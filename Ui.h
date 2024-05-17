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
	/// タイマーを表示する
	/// </summary>
	void DrawTimer();

	/// <summary>
	/// 試合が終了した時に呼ぶ
	/// </summary>
	/// <param name="player">勝った方が1P側かどうか</param>
	void SetFinish(bool player) { m_isWinPlayer = player; m_isFinish = true; }

	/// <summary>
	/// 試合が引き分けで終わった時に呼ぶ
	/// </summary>
	void SetDraw() { m_isDraw = true; }

	/// <summary>
	/// ゲームシーンから現在何秒か取得する
	/// </summary>
	/// <param name="time">制限時間が今何秒か</param>
	void SetTimer(int time) { m_timer = time; }

	/// <summary>
	/// 試合終了時の演出が終わったのを取得する
	/// </summary>
	/// <returns>試合が終了したかどうか</returns>
	bool GetFinishStaging() { return !m_isStagingGraphShake; }

private:
	bool m_isFinish;//ゲームが終了したか

	int m_timer;//制限時間を表示する

	bool m_isWinPlayer;//どちらのプレイヤーが勝ったか

	bool m_isDraw;//引き分けかどうか

	/*勝ち負けが決まったときに表示する画像ハンドル*/
	int m_winPlayerGraph;
	int m_winEnemyGraph;
	int m_drawGraph;

	/*試合終了時の画像関係*/
	double m_stagingGraphScale;//サイズ
	bool m_isStagingGraphShake;//揺らしているかどうか
	VECTOR m_stagingGraphPos;//表示座標
	int m_shakeTime;//揺らした時間

	std::map<char, int> m_timerMap;//0~9までの数字が入っている
};

