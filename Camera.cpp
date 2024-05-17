#include "Camera.h"

namespace
{
	constexpr float kCameraSpeed = 10.0f;//カメラが移動するスピード
	constexpr float kWinCameraDistance = 200.0f;//試合が終わった時にキャラにどれだけ近づくか

	const VECTOR kWinCameraPos = VGet(0,400.0f,-300.0f);//勝利したキャラから見たカメラの座標

	const VECTOR kCameraInitPos = VGet(0, 800, -1200);//カメラの初期座標

	const VECTOR kCameraAngle = VGet(0.5, 0,0);//カメラのアングル

	constexpr float kShiftTargetPos = 1.3;//カメラの位置をどれだけずらすか


}
Camera::Camera() :
	m_pos(),
	m_targetPos(),
	m_isFinish(false)
{
	SetCameraNearFar(10.0f, 3500.0f);
	m_pos = kCameraInitPos;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (m_isFinish)
	{
		//ターゲットとの距離を計る
		VECTOR distanceVec = VSub(m_targetPos,m_pos);
		float distance = VSize(distanceVec);
		if (distance > kWinCameraDistance)
		{
			m_pos = VAdd(m_pos, m_moveVec);
		}
	}
	SetCameraPositionAndAngle(m_pos, kCameraAngle.x, kCameraAngle.y, kCameraAngle.z);
}

void Camera::SetWinner(VECTOR pos)
{
	//ターゲットの座標を代入
	m_targetPos = VAdd(pos,kWinCameraPos);
	m_targetPos.x *= kShiftTargetPos;
	//移動ベクトルを作成
	VECTOR dirVec = VSub(m_targetPos,m_pos);
	m_moveVec = VNorm(dirVec);
	m_moveVec = VScale(m_moveVec,kCameraSpeed);

	m_isFinish = true;
}

