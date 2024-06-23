#include "Enemy.h"

#include "../../Scene/SceneManager.h"
#include "../Player/Player.h"

void Enemy::SetTarget(std::weak_ptr<Player> _target)
{
	if (!_target.expired())
	{
		m_wpPlayer = _target;
	}
}

void Enemy::Init()
{
	m_pos = {};
	m_dir = {};
	m_spd = 0.05f;
	m_gravity = 0;
	m_animeCnt = 0;
	m_animeSpeed = 0.1f;
	m_bChase = false;
	m_searchArea = 3.0f;
	m_spPolygon = std::make_shared<KdSquarePolygon>();
	m_spPolygon->SetMaterial("Asset/Textures/Enemy.png");
	m_spPolygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_spPolygon->SetSplit(6, 6);
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyDamage", {0,0.5f,0},0.3f, KdCollider::Type::TypeDamage);
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Enemy::Update()
{
	m_dir = {};

	int Walk[4] = {3,4,3,5};

	m_animeCnt += m_animeSpeed;
	if (m_animeCnt >= 4)
	{
		m_animeCnt = 0;
	}

	m_spPolygon->SetUVRect(Walk[(int)m_animeCnt]);

	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3(0, 0.5f, 0), 0.3f,kBlueColor);

	if (!m_wpPlayer.expired())
	{
		Math::Vector3 targetPos = m_wpPlayer.lock()->GetPos();
		Math::Vector3 vec;
		vec = targetPos - m_pos;

		m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3(0.0f,0.5f,0.0f), m_searchArea, kGreenColor);

		if (vec.Length() < m_searchArea && vec.Length() > 0.1f)
		{
			m_bChase = true;
		}
		else
		{
			m_bChase = false;
		}

		if (m_bChase)
		{
			vec.y = 0;
			vec.Normalize();
			m_dir = vec;
		}
	}

	m_dir.Normalize();
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;
	m_pos += m_dir * m_spd;

	KdCollider::RayInfo ray;
	ray.m_pos = m_pos;
	ray.m_pos.y += 0.1f;

	//少しの段差を許容する
	const float enableStepHigh = 0.2f;
	ray.m_pos.y += enableStepHigh;
	//補正した分レイを伸ばす
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

	//コライダーを使ったチェイス
	//KdCollider::SphereInfo sphere;
	//sphere.m_sphere.Center = m_pos;
	//sphere.m_sphere.Center.y += 0.5f;
	//sphere.m_sphere.Radius = 3.0f;
	//sphere.m_type = KdCollider::Type::TypeSight;
	//
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center,sphere.m_sphere.Radius,kGreenColor);

	//retList.clear();

	//for (std::shared_ptr<KdGameObject> obj : SceneManager::Instance().GetObjList())
	//{
	//	obj->Intersects(sphere, &retList);
	//}

	//maxOverLap = 0.0f;
	//Math::Vector3 hitDir = {};
	//isHit = false;
	//for (const KdCollider::CollisionResult& ret : retList)
	//{
	//	if (maxOverLap < ret.m_overlapDistance)
	//	{
	//		maxOverLap = ret.m_overlapDistance;
	//		hitDir = ret.m_hitDir;
	//		isHit = true;
	//	}
	//}

	//if (isHit)
	//{
	//	hitDir.y = 0;
	//	hitDir.Normalize();
	//	m_dir = hitDir * -1;

	//	m_pos += m_dir * m_spd;
	//}
}

void Enemy::PostUpdate()
{
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPolygon, m_mWorld);
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPolygon, m_mWorld);
}
