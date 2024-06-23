#include "Attack.h"

#include "../../Scene/SceneManager.h"

void Attack::Init()
{
	m_animeSpeed = 1.0f;
	m_attackArea = 0.3f;

	m_spPolygon = std::make_shared<KdSquarePolygon>();
	m_spPolygon->SetMaterial("Asset/Textures/Attack.png");
	m_spPolygon->SetSplit(9, 1);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Attack::Update()
{
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = m_mWorld.Translation();
	sphere.m_sphere.Radius = m_attackArea;
	sphere.m_type = KdCollider::Type::TypeDamage;

	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

	for (std::shared_ptr<KdGameObject> obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, nullptr))
		{
			obj->OnHit();

			OnHit();
			break;
		}
	}

	m_animeCnt += m_animeSpeed;
	if (m_animeCnt >= 9.0f)
	{
		m_isExpired = true;
	}
	m_spPolygon->SetUVRect((int)m_animeCnt);
}

void Attack::DrawUnLit()
{
	if (m_spPolygon != nullptr)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPolygon, m_mWorld);
	}
}
