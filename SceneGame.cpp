#include "SceneGame.h"
#include "SceneTitle.h"
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Obstruct.h"
#include "Ui.h"
namespace
{
	constexpr int kTimelimit = 30;//制限時間
	constexpr int kFramelate = 60;//フレームレート
	constexpr int kFinishDamage = 36;//ダメージの限界値

	constexpr int kBgmVol = 150;//BGMの大きさ

	constexpr int kCountDownTime = 3;//カウントダウンの時間
}
SceneGame::SceneGame(SceneManager& sceneManager, DataManager& dataManager) :
	SceneBase(sceneManager, dataManager),
	m_isFinish(false),
	m_timer(kTimelimit),
	m_timeCount(0),
	m_isDraw(false),
	m_isStartGame(false),
	m_countDown(kCountDownTime)

{
	m_pPlayer = std::make_shared<Player>();
	m_pEnemy = std::make_shared<Enemy>();
	m_pCamera = std::make_shared<Camera>();
	m_pObstruct = std::make_shared<Obstruct>();
	m_pUi = std::make_shared<Ui>();

	m_drawSound = LoadSoundMem("data/sound/draw.mp3");
	m_finishGameSound = LoadSoundMem("data/sound/finishBattle.mp3");
	m_winGameSound = LoadSoundMem("data/sound/win.mp3");
	m_startGameSound = LoadSoundMem("data/sound/startBattle.mp3");
	m_bgmSound = LoadSoundMem("data/sound/gameSceneBgm.mp3");
	ChangeVolumeSoundMem(kBgmVol, m_bgmSound);
}

SceneGame::~SceneGame()
{
	StopSoundMem(m_startGameSound);
	StopSoundMem(m_drawSound);
	StopSoundMem(m_winGameSound);
	StopSoundMem(m_finishGameSound);
	StopSoundMem(m_bgmSound);
}

void SceneGame::Init()
{
	m_pPlayer->Init();
	m_pEnemy->Init();
	m_pObstruct->Init();
	m_pUi->Init();

	PlaySoundMem(m_startGameSound, DX_PLAYTYPE_BACK);
	PlaySoundMem(m_bgmSound, DX_PLAYTYPE_LOOP);
}

void SceneGame::Update(Input input)
{
	int pad = GetJoypadInputState(PAD_INPUT_1);
	//カウントダウン処理
	if (!m_isStartGame)
	{
		m_timeCount++;
		if (m_timeCount > kFramelate)
		{
			m_countDown--;
			m_timeCount = 0;
		}
		if (m_countDown <= 0)
		{
			m_isStartGame = true;
		}
	}
	else
	{
		m_pPlayer->Update(m_pEnemy,input);
		m_pEnemy->Update(m_pPlayer,input);
	}
	m_pCamera->Update();
	m_pObstruct->Update();
	m_pUi->Update();
	//ゲームが終了していない時の処理
	if (!m_isFinish && m_isStartGame)
	{
		//時間を経過させる
		m_timeCount++;
		//60フレーム数えたら
		if (m_timeCount > kFramelate)
		{
			m_timeCount = 0;
			//制限時間を減らす
			m_timer--;
			//Uiに制限時間を渡す
			m_pUi->SetTimer(m_timer);
		}
		//タイマーが0秒になったら
		if (m_timer <= 0)
		{
			//現時点で勝っている方を取得する
			if (m_pPlayer->GetDamage() > 0)
			{
				//プレイヤーだった場合
				FinishGame(true);
			}
			else if (m_pPlayer->GetDamage() < 0)
			{
				//エネミーだった場合
				FinishGame(false);
			}
			else
			{
				//引き分けだった場合
				DrawGame();
			}
		}
		//ダメージを一定量以上受けたら
		if (m_pPlayer->GetDamage() > kFinishDamage)
		{
			//プレイヤーの勝ち
			FinishGame(true);
		}
		else if (m_pPlayer->GetDamage() < -kFinishDamage)
		{
			//エネミー側の勝ち
			FinishGame(false);
		}
	}
	else
	{
		if (CheckHitKeyAll() && m_pUi->GetFinishStaging())
		{
			m_sceneManager.ChangeScene(std::make_shared<SceneTitle>(m_sceneManager, m_dataManager));
			return;
		}
	}
}

void SceneGame::Draw()
{
	m_pPlayer->Draw();
	m_pEnemy->Draw();
	m_pObstruct->Draw();
	if (!m_isStartGame)
	{
		m_pUi->DrawCountDown(m_countDown);
	}
	else
	{
		m_pUi->Draw();
	}
}

void SceneGame::End()
{
}

void SceneGame::FinishGame(bool player)
{
	m_pPlayer->SetFinish(player);
	m_pEnemy->SetFinish(player);
	m_pUi->SetFinish(player);
	m_isFinish = true;
	PlaySoundMem(m_finishGameSound, DX_PLAYTYPE_BACK);
	PlaySoundMem(m_winGameSound, DX_PLAYTYPE_BACK);
	if (player)
	{
		m_pCamera->SetWinner(m_pPlayer->GetPos());
	}
	else
	{
		m_pCamera->SetWinner(m_pEnemy->GetPos());
	}
}

void SceneGame::DrawGame()
{
	m_isFinish = true;
	m_isDraw = true;

	PlaySoundMem(m_finishGameSound, DX_PLAYTYPE_BACK);
	PlaySoundMem(m_drawSound, DX_PLAYTYPE_BACK);

	m_pPlayer->SetDraw();
	m_pEnemy->SetDraw();
	m_pUi->SetDraw();
}
