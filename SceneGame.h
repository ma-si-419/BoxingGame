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
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//終了処理
	void End();
	//勝ち負けが決まった時に呼ぶ関数
	void FinishGame(bool player);
private:

	bool m_isFinish;//ゲームが終了したかどうか

	int m_timer;//制限時間

	int m_timeCount;//時間を数えるときに使用

	//ポインタ
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Obstruct> m_pObstruct;
	std::shared_ptr<Ui> m_pUi;
};

