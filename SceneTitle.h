#pragma once
#include "SceneBase.h"
#include <memory>
class Camera;
class SceneTitle : public SceneBase
{
public:
	SceneTitle(SceneManager& sceneManager, DataManager& dataManager);
	~SceneTitle();
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//終了処理
	void End();
private:
	int m_logoHandle;//タイトルロゴのハンドル
	int m_charactermodel[2];//キャラクターのモデル
	int m_domemodel;//スカイドームのハンドル

	std::shared_ptr<Camera> m_pCamera;

};