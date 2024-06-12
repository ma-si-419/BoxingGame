#include "SceneTitle.h"
#include "SceneGame.h"
#include "Camera.h"
namespace
{
	//パンチ時のモーションナンバー
	constexpr int kPunchAnimNumber = 10;
	//左のキャラクターの座標
	const VECTOR kLeftCharPos = VGet(-160, 250, -750);
	//右のキャラクターの座標
	const VECTOR kRightCharPos = VGet(160, 250, -735);
	//左のキャラクターの回転度
	const VECTOR kLeftCharAngle = VGet(0, static_cast<float>((DX_PI_F / 180) * 280), 0);
	//右のキャラクターの回転度
	const VECTOR kRightCharAngle = VGet(0, static_cast<float>((DX_PI_F / 180) * 80), 0);
	//左のキャラクターのアニメーションの時間
	constexpr float kLeftCharAnimTime = 7.0f;
	//右のキャラクターのアニメーションの時間
	constexpr float kRightCharAnimTime = 13.5f;
	//スカイドームの大きさ
	const VECTOR kSkyDomeScale = VGet(15, 15, 7);
	//シーンを選択する指の座標
	constexpr int kFingerPosX = 150;
	constexpr int kFingerPosY[2] = { 345,415 };
	//指を揺らすスピード
	constexpr float kFingerShakeSpeed = 0.3f;
	//指を揺らす大きさ
	constexpr int kFingerShakeScale = 10;
	//BGMの大きさ
	constexpr int kBgmVol = 150;
}
SceneTitle::SceneTitle(SceneManager& sceneManager, DataManager& dataManager) :
	SceneBase(sceneManager, dataManager),
	m_logoHandle(-1),
	m_characterModel(),
	m_domeModel(-1),
	m_fingerHandle(-1),
	m_fingerPos(),
	m_fingerShake(0),
	m_selectCommand(Command::kStart)
{
	m_logoHandle = LoadGraph("data/image/titleImage.png");
	m_fingerHandle = LoadGraph("data/image/finger.png");
	m_domeModel = MV1LoadModel("data/model/Dome.mv1");

	m_bgmSound = LoadSoundMem("data/sound/selectSceneBgm.mp3");
	ChangeVolumeSoundMem(kBgmVol,m_bgmSound);

	MV1SetScale(m_domeModel, kSkyDomeScale);

	InitChar();

	m_pCamera = std::make_shared<Camera>();

	m_fingerPos = VGet(kFingerPosX, kFingerPosY[0], 0);
}

SceneTitle::~SceneTitle()
{
	MV1DeleteModel(m_characterModel[0]);
	MV1DeleteModel(m_characterModel[1]);
	MV1DeleteModel(m_domeModel);

	StopSoundMem(m_bgmSound);
}

void SceneTitle::Init()
{
	PlaySoundMem(m_bgmSound, DX_PLAYTYPE_LOOP);
}

void SceneTitle::Update(Input input)
{
	m_pCamera->Update();
	if (input.IsTrigger("up"))
	{
		m_fingerPos.y = kFingerPosY[0];
		m_selectCommand = Command::kStart;
	}
	else if (input.IsTrigger("down"))
	{
		m_fingerPos.y = kFingerPosY[1];
		m_selectCommand = Command::kEnd;
	}
	//エンターキーが押されたとき
	if (input.IsTrigger("ok"))
	{
		if (m_selectCommand == Command::kStart)
		{
			m_sceneManager.ChangeScene(std::make_shared<SceneGame>(m_sceneManager, m_dataManager));
		}
		else if (m_selectCommand == Command::kEnd)
		{
			m_sceneManager.GameEnd();
		}
	}


	m_fingerShake += kFingerShakeSpeed;

	float fingerShakeX = sin(m_fingerShake) * kFingerShakeScale;

	m_fingerPos.x = kFingerPosX + fingerShakeX;

}

void SceneTitle::Draw()
{

	DrawString(0, 0, "SceneTitle", GetColor(255, 255, 255));

	MV1DrawModel(m_characterModel[0]);

	MV1DrawModel(m_characterModel[1]);

	MV1DrawModel(m_domeModel);

	DrawGraph(0, 0, m_logoHandle, true);

	DrawGraph(m_fingerPos.x, m_fingerPos.y, m_fingerHandle, true);

}

void SceneTitle::End()
{
	MV1DeleteModel(m_characterModel[0]);
	MV1DeleteModel(m_characterModel[1]);
}

void SceneTitle::InitChar()
{
	m_characterModel[0] = MV1LoadModel("data/model/Player.mv1");
	m_characterModel[1] = MV1LoadModel("data/model/Player.mv1");

	MV1SetPosition(m_characterModel[0], kLeftCharPos);
	MV1SetPosition(m_characterModel[1], kRightCharPos);

	MV1SetRotationXYZ(m_characterModel[0], kLeftCharAngle);
	MV1SetRotationXYZ(m_characterModel[1], kRightCharAngle);

	int attachAnim[2];

	attachAnim[0] = MV1AttachAnim(m_characterModel[0], kPunchAnimNumber);
	attachAnim[1] = MV1AttachAnim(m_characterModel[1], kPunchAnimNumber);

	MV1SetAttachAnimTime(m_characterModel[0], attachAnim[0], kLeftCharAnimTime);
	MV1SetAttachAnimTime(m_characterModel[1], attachAnim[1], kRightCharAnimTime);
}
