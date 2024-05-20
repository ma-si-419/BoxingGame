#include "Ui.h"
#include "Game.h"
#include <string>
namespace
{
	constexpr int kTimelimit = 30;//制限時間

	constexpr int kTimerScale = 30;//タイマーの文字の大きさ

	/*タイマーの座標*/
	constexpr int kTimerPosX = 250;
	constexpr int kTimerPosY = 10;

	/*試合終了時の画像関係*/
	constexpr double kStagingGraphInitSize = 10.0;//初期サイズ
	constexpr double kStagingSpeed = 0.3;	//縮小スピード
	constexpr int kStagingShakeTime = 2;	//揺らす時間
	constexpr int kStagingShakeScale = 40;	//揺れの大きさ

}
Ui::Ui() :
	m_isFinish(false),
	m_timer(kTimelimit),
	m_isWinPlayer(false),
	m_isDraw(false),
	m_stagingGraphScale(kStagingGraphInitSize),
	m_isStagingGraphShake(true),
	m_shakeTime(0),
	m_isPad(true)
{
	m_stagingGraphPos = VGet(Game::kWindowWidth / 2, Game::kWindowHeight / 2, 0);

	m_winPlayerGraph = LoadGraph("data/image/winPlayer.png");
	m_winEnemyGraph = LoadGraph("data/image/winEnemy.png");
	m_drawGraph = LoadGraph("data/image/draw.png");
	m_keyManualGraph = LoadGraph("data/image/keyManual.png");
	m_padManualGraph = LoadGraph("data/image/padManual.png");

	m_timerMap['0'] = LoadGraph("data/image/zero.png");
	m_timerMap['1'] = LoadGraph("data/image/one.png");
	m_timerMap['2'] = LoadGraph("data/image/two.png");
	m_timerMap['3'] = LoadGraph("data/image/three.png");
	m_timerMap['4'] = LoadGraph("data/image/four.png");
	m_timerMap['5'] = LoadGraph("data/image/five.png");
	m_timerMap['6'] = LoadGraph("data/image/six.png");
	m_timerMap['7'] = LoadGraph("data/image/seven.png");
	m_timerMap['8'] = LoadGraph("data/image/eight.png");
	m_timerMap['9'] = LoadGraph("data/image/nine.png");
}

Ui::~Ui()
{
}

void Ui::Init()
{

}

void Ui::Update()
{
	//ゲームが終了したら
	if (m_isDraw || m_isFinish)
	{

		//縮小しすぎないように
		if (m_stagingGraphScale > 1.0)
		{
			m_stagingGraphScale -= kStagingSpeed;
		}
		//縮小しきったら
		else if (m_isStagingGraphShake)
		{
			//少しだけ揺らす
			m_stagingGraphPos.x += GetRand(kStagingShakeScale) - kStagingShakeScale / 2;
			m_stagingGraphPos.y += GetRand(kStagingShakeScale) - kStagingShakeScale / 2;

			m_shakeTime++;
			//一定時間揺らしたら
			if (m_shakeTime > kStagingShakeTime)
			{
				//揺れを止める
				m_isStagingGraphShake = false;
				//最初の座標に戻す
				m_stagingGraphPos = VGet(Game::kWindowWidth / 2, Game::kWindowHeight / 2, 0);
			}
		}
	}
}

void Ui::Draw()
{
	/*常に表示する*/
	if (m_isPad)
	{
		DrawGraph(0, 0, m_padManualGraph, true);
	}
	else
	{
		DrawGraph(0, 0, m_keyManualGraph, true);
	}
	DrawTimer();

	/*ゲーム終了した時の演出*/
	if (m_isFinish)
	{
		if (m_isWinPlayer)
		{
			DrawRotaGraph(m_stagingGraphPos.x, m_stagingGraphPos.y, m_stagingGraphScale, 0, m_winPlayerGraph, true);
		}
		else
		{
			DrawRotaGraph(m_stagingGraphPos.x, m_stagingGraphPos.y, m_stagingGraphScale, 0, m_winEnemyGraph, true);
		}
	}
	//引き分けで終わった時の演出
	if (m_isDraw)
	{
		DrawRotaGraph(m_stagingGraphPos.x, m_stagingGraphPos.y, m_stagingGraphScale, 0, m_drawGraph, true);
	}

}

void Ui::DrawTimer()
{
	//タイマーが今何秒か取得
	std::string timeNumber = std::to_string(m_timer);
	//一桁目をchar型に保存
	char temp = timeNumber.at(0);
	//タイマーが一桁の場合
	if (m_timer < 10)
	{
		//画像を一つ表示するだけ
		DrawGraph(kTimerPosX, kTimerPosY, m_timerMap[temp], true);
	}
	//タイマーが二桁の場合
	else
	{
		//二桁目の数字をchar型に保存
		char temp2 = timeNumber.at(1);
		//画像を二つ表示する
		DrawGraph(kTimerPosX - kTimerScale, kTimerPosY, m_timerMap[temp], true);
		DrawGraph(kTimerPosX + kTimerScale, kTimerPosY, m_timerMap[temp2], true);
	}
}

void Ui::DrawCountDown(int time)
{
	//タイマーが今何秒か取得
	std::string timeNumber = std::to_string(time);
	//一桁目をchar型に保存
	char temp = timeNumber.at(0);
	//画像を表示する
	DrawRotaGraph(Game::kWindowWidth / 2,Game::kWindowHeight / 2,2.0,0.0, m_timerMap[temp], true);
}
