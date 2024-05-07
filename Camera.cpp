#include "Camera.h"

Camera::Camera() :
	m_pos(),
	m_angle()
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
	SetCameraPositionAndAngle(m_pos, m_angle.x, m_angle.y, m_angle.z);
}
