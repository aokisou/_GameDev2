#include "Player.h"

#include "../../Camera/CameraBase.h"
#include "../../../main.h"
#include "../../../Scene/SceneManager.h"

void Player::Init()
{
	m_pos = {};

	m_pos.y += m_adjustHeight;

	m_moveDir = {};

	m_gravity = {};

	m_fixMousePos = { 640,360 };

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

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_bJump)
		{
			m_gravity = -m_jumpPow;
			m_bJump = true;
		}
	}
	else
	{
		m_bJump = false;
	}

	UpdateRotateByMouse();

	if (m_moveDir.LengthSquared() != 0)
	{
		m_moveDir = m_moveDir.TransformNormal(m_moveDir,GetRotationYMatrix());
	}

	m_moveDir.Normalize();
	m_pos += m_moveDir * m_movePow;

	m_gravity += m_gravityPow;
	m_pos.y -= m_gravity;

	Math::Matrix rotateMat,transMat;
	rotateMat = GetRotationMatrix();
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = rotateMat * transMat;
}

void Player::PostUpdate()
{
	KdCollider::RayInfo ray;
	ray.m_pos = m_pos;
	ray.m_pos.y -= m_adjustHeight;

	const float enableStepHigh = 0.5f;
	ray.m_pos.y += enableStepHigh;
	ray.m_range = enableStepHigh + m_gravity;

	ray.m_dir = Math::Vector3::Down;
	ray.m_type = KdCollider::Type::TypeGround;

	std::list<KdCollider::CollisionResult> retList;

	float maxOverLap = {};
	Math::Vector3 hitPos = {};

	for (const std::shared_ptr<KdGameObject>& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(ray, &retList))
		{
			m_gravity = 0;

			for (const KdCollider::CollisionResult& ret : retList)
			{
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					hitPos = ret.m_hitPos;
				}
			}

			m_pos = hitPos + Math::Vector3(0,m_adjustHeight,0);

			retList.clear();
		}
	}
}

void Player::UpdateRotateByMouse()
{
	// マウスでカメラを回転させる処理
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_fixMousePos.x;
	_mouseMove.y = _nowPos.y - m_fixMousePos.y;

	SetCursorPos(m_fixMousePos.x, m_fixMousePos.y);

	// 実際にカメラを回転させる処理(0.15はただの補正値)
	m_degAng.x += _mouseMove.y * 0.15f;
	m_degAng.y += _mouseMove.x * 0.15f;

	// 回転制御
	m_degAng.x = std::clamp(m_degAng.x, -45.f, 45.f);
}
