#include "Player.h"

#include "../../Camera/CameraBase.h"
#include "../../../main.h"

void Player::Init()
{
	m_pos = {};
	m_moveDir = {};

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::Update()
{
	m_moveDir = {};

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_moveDir += Math::Vector3::Backward;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_moveDir += Math::Vector3::Forward;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_moveDir += Math::Vector3::Left;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_moveDir += Math::Vector3::Right;
	}

	if (!m_wpCamera.expired())
	{
		m_moveDir = m_moveDir.TransformNormal(m_moveDir, m_wpCamera.lock()->GetRotationYMatrix());
	}

	m_moveDir.Normalize();
	m_pos += m_moveDir * m_movePow;

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Player::DrawLit()
{
}
