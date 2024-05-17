#include "Camera.h"

namespace
{
	constexpr float kCameraSpeed = 10.0f;//�J�������ړ�����X�s�[�h
	constexpr float kWinCameraDistance = 200.0f;//�������I��������ɃL�����ɂǂꂾ���߂Â���

	const VECTOR kWinCameraPos = VGet(0,400.0f,-300.0f);//���������L�������猩���J�����̍��W

	const VECTOR kCameraInitPos = VGet(0, 800, -1200);//�J�����̏������W

	const VECTOR kCameraAngle = VGet(0.5, 0,0);//�J�����̃A���O��

	constexpr float kShiftTargetPos = 1.3;//�J�����̈ʒu���ǂꂾ�����炷��


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
		//�^�[�Q�b�g�Ƃ̋������v��
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
	//�^�[�Q�b�g�̍��W����
	m_targetPos = VAdd(pos,kWinCameraPos);
	m_targetPos.x *= kShiftTargetPos;
	//�ړ��x�N�g�����쐬
	VECTOR dirVec = VSub(m_targetPos,m_pos);
	m_moveVec = VNorm(dirVec);
	m_moveVec = VScale(m_moveVec,kCameraSpeed);

	m_isFinish = true;
}

