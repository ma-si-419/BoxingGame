#include "Camera.h"

Camera::Camera() :
	m_pos(),
	m_angle()
{
	SetCameraNearFar(10.0f, 800.0f);
	m_pos = VGet(0, 600, -600);
	m_angle = VGet(0.5, 0, 0);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	SetCameraPositionAndAngle(m_pos, m_angle.x, m_angle.y, m_angle.z);
}
