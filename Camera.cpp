#include "Camera.h"

namespace
{
	constexpr float kCameraSpeed = 10.0f;
	constexpr float kWinCameraDistance = 200.0f;

	const VECTOR kWinCameraPos = VGet(0,300.0f,-300.0f);
}
Camera::Camera() :
	m_pos(),
	m_angle(),
	m_targetPos(),
	m_isFinish(false)
{
	SetCameraNearFar(10.0f, 3500.0f);
	m_pos = VGet(0, 800, -1200);
	m_angle = VGet(0.5, 0, 0);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (m_isFinish)
	{
		//�^�[�Q�b�g�Ƃ̋������v��
		VECTOR distanceVec = VSub(m_targetPos,m_pos);
		float distance = VSize(distanceVec);
		if (distance > kWinCameraDistance)
		{
			m_pos = VAdd(m_pos, m_moveVec);
		}
	}
	SetCameraPositionAndAngle(m_pos, m_angle.x, m_angle.y, m_angle.z);
}

void Camera::SetWinner(VECTOR pos)
{
	//�^�[�Q�b�g�̍��W����
	m_targetPos = VAdd(pos,kWinCameraPos);
	//�ړ��x�N�g�����쐬
	VECTOR dirVec = VSub(pos,m_pos);
	m_moveVec = VNorm(dirVec);
	m_moveVec.x *= 1.5f;
	m_moveVec = VScale(m_moveVec,kCameraSpeed);

	m_isFinish = true;
}

