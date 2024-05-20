#pragma once
#include "SceneBase.h"
#include "DxLib.h"
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
	enum class Command
	{
		kStart,
		kEnd
	};
	//キャラクターの初期化処理
	void InitChar();
	int m_logoHandle;//タイトルロゴのハンドル
	int m_characterModel[2];//キャラクターのモデル
	int m_domeModel;//スカイドームのハンドル
	int m_fingerHandle;//指の画像ハンドル
	VECTOR m_fingerPos;//指の座標

	bool m_isHitKey;//前のフレームでエンターキーを押していたか

	float m_fingerShake;//指の揺らす座標

	Command m_selectCommand;//選んでいる項目

	std::shared_ptr<Camera> m_pCamera;//カメラのポイント

	int m_bgmSound;//BGM

};