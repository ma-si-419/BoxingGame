#pragma once
#include<memory>
class SceneBase;
class SceneManager
{
public:
	//コンストラクタ
	SceneManager();
	//デストラクタ
	~SceneManager();

	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//別のシーンに移動する際に使用する関数
	void ChangeScene(std::shared_ptr<SceneBase> next);
private:
	std::shared_ptr<SceneBase> m_pScene;
};

