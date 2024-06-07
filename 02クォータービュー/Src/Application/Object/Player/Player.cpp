#include "Player.h"

#include "../../Scene/SceneManager.h"

void Player::Init()
{
	m_pos = {};
	m_dir = {};
	m_spd = 0.1f;
	m_gravity = 0.0f;
	m_dirType = DirType::Down;
	m_animeInfo.start = 4;
	m_animeInfo.end = m_animeInfo.start + 3;
	m_animeInfo.cnt = 0.0f;
	m_animeInfo.speed = 0.2f;
	m_polygon.SetMaterial("Asset/Textures/player.png");
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon.SetSplit(4, 8);
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::Update()
{
	//if (GetAsyncKeyState(VK_UP)) { m_pos.z += m_spd; }
	//if (GetAsyncKeyState(VK_DOWN)) { m_pos.z -= m_spd; }
	//if (GetAsyncKeyState(VK_LEFT)) { m_pos.x -= m_spd; }
	//if (GetAsyncKeyState(VK_RIGHT)) { m_pos.x += m_spd; }

	m_dir = { 0,0,0 };
	UINT oldDirType = m_dirType;
	m_dirType = 0;
	if (GetAsyncKeyState(VK_UP)) 
	{ 
		m_dir.z += 1;
		m_dirType |= DirType::Up;
	}
	if (GetAsyncKeyState(VK_DOWN)) 
	{ 
		m_dir.z -= 1;
		m_dirType |= DirType::Down;
	}
	if (GetAsyncKeyState(VK_LEFT)) 
	{ 
		m_dir.x -= 1;
		m_dirType |= DirType::Left;
	}
	if (GetAsyncKeyState(VK_RIGHT)) 
	{
		m_dir.x += 1;
		m_dirType |= DirType::Right;
	}
	if (GetAsyncKeyState(VK_SPACE)) { m_gravity = -0.1f; }

	if (m_dirType != oldDirType && m_dirType != 0)
	{
		ChangeAnimation();
	}
	else
	{
		m_dirType = oldDirType;
	}

	m_dir.Normalize();
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;
	m_pos += m_dir * m_spd;

	int animeCnt = 0;

	m_animeInfo.cnt += m_animeInfo.speed;

	animeCnt = m_animeInfo.start + (int)m_animeInfo.cnt;
	if (animeCnt > m_animeInfo.end)
	{
		animeCnt = m_animeInfo.start;
		m_animeInfo.cnt = 0;
	}

	m_polygon.SetUVRect(animeCnt);

	KdCollider::RayInfo ray;
	ray.m_pos = m_pos;
	ray.m_pos.y += 0.1f;

	//少しの段差を許容する
	const float enableStepHigh = 0.2f;
	ray.m_pos.y += enableStepHigh;
	ray.m_range = m_gravity + enableStepHigh + 0.1f;

	ray.m_dir = Math::Vector3::Down;
	ray.m_type = KdCollider::Type::TypeGround;

	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	std::list<KdCollider::CollisionResult> retList;

	for (std::shared_ptr<KdGameObject> obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(ray, &retList);
	}

	float maxOverLap = 0.0f;
	Math::Vector3 hitPos;
	bool isHit = false;
	for (const KdCollider::CollisionResult& ret : retList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			isHit = true;
		}
	}

	if (isHit)
	{
		m_pos = hitPos;
		m_gravity = 0.0f;
	}
}

void Player::PostUpdate()
{
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Player::ChangeAnimation()
{
	switch (m_dirType)
	{
	case DirType::Up:
	case DirType::Up + DirType::Right + DirType::Left:
		m_animeInfo.start = 24;
		m_animeInfo.end = m_animeInfo.start + 3;
		break;
	case DirType::Down:
	case DirType::Down + DirType::Right + DirType::Left:
		m_animeInfo.start = 4;
		m_animeInfo.end = m_animeInfo.start + 3;
		break;
	case DirType::Left:
	case DirType::Up + DirType::Down + DirType::Left:
		m_animeInfo.start = 12;
		m_animeInfo.end = m_animeInfo.start + 3;
		break;
	case DirType::Right:
	case DirType::Up + DirType::Down + DirType::Right:
		m_animeInfo.start = 16;
		m_animeInfo.end = m_animeInfo.start + 3;
		break;
	case DirType::Up + DirType::Left:
		m_animeInfo.start = 20;
		m_animeInfo.end = m_animeInfo.start + 3;
		break;
	case DirType::Up + DirType::Right:
		m_animeInfo.start = 28;
		m_animeInfo.end = m_animeInfo.start + 3;
		break;
	case DirType::Down + DirType::Left:
		m_animeInfo.start = 0;
		m_animeInfo.end = m_animeInfo.start + 3;
		break;
	case DirType::Down + DirType::Right:
		m_animeInfo.start = 8;
		m_animeInfo.end = m_animeInfo.start + 3;
		break;
	}

	m_animeInfo.cnt = 0;
	m_animeInfo.speed = 0.2f;
}
