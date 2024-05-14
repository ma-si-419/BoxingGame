#include "Ui.h"
#include "DxLib.h"
namespace
{
	constexpr int kTimelimit = 30;
}
Ui::Ui():
	m_isFinish(false),
	m_timer(kTimelimit)
{
	m_winPlayerGraph = LoadGraph("data/image/winPlayer.png");
	m_winEnemyGraph = LoadGraph("data/image/winEnemy.png");
}

Ui::~Ui()
{
}

void Ui::Init()
{
	
}

void Ui::Update()
{
}

void Ui::Draw()
{
	//ÉQÅ[ÉÄèIóπÇµÇΩéûÇÃââèo
	if (m_isFinish)
	{
		if (m_isWinPlayer)
		{
			DrawGraph(0, 0, m_winPlayerGraph,true);
		}
		else
		{
			DrawGraph(0, 0, m_winEnemyGraph, true);
		}
	}
	DrawFormatString(320, 100, GetColor(0, 0, 0), "%d", m_timer);
}
