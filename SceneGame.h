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
	/// 初期化処理
	/// </summary>
	void Init();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 終了処理
	/// </summary>
	void End();
	/// <summary>
	/// 勝ち負けが決まった時に呼ぶ関数
	/// </summary>
	/// <param name="player">1P側が勝ったかどうか</param>
	void FinishGame(bool player);
	/// <summary>
	/// 引き分けになった時に呼ぶ関数
	/// </summary>
	void DrawGame();
private:

	bool m_isFinish;//ゲームが終了したかどうか

	bool m_isDraw;//引き分けかどうか

	int m_timer;//制限時間

	int m_timeCount;//時間を数えるときに使用

	/*サウンド関係*/
	int m_startGameSound;//試合が始まった時の効果音
	int m_drawSound;//引き分けになった時の効果音
	int m_winGameSound;//どちらかが勝った時の効果音
	int m_finishGameSound;//勝負が終わった時の効果音
	int m_bgmSound;//BGM

	//ポインタ
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Obstruct> m_pObstruct;
	std::shared_ptr<Ui> m_pUi;
};

