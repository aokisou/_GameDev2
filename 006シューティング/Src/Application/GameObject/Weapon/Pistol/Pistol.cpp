#include "Pistol.h"

#include "../../../Scene/SceneManager.h"

void Pistol::Init()
{
	std::shared_ptr<KdModelData> model = std::make_shared<KdModelData>();
	model->Load("Asset/Models/Weapon/Pistol/Pistol.gltf");
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData(model);

	m_localMat = Math::Matrix::CreateTranslation({0.35f,-0.25f,0.2f});

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Pistol::Update()
{
	WeaponBase::Update();
}

void Pistol::Shot(const bool _bRay)
{
	if (!m_wpParent.expired())
	{
		const std::shared_ptr<const KdGameObject> parent = m_wpParent.lock();
		KdCollider::RayInfo ray;
		ray.m_pos = parent->GetPos();
		ray.m_dir = Math::Vector3::Backward;
		ray.m_dir = Math::Vector3::TransformNormal(ray.m_dir,parent->GetMatrix());
		ray.m_range = 1000.f;
		ray.m_type = KdCollider::Type::TypeGround;

		std::list<KdCollider::CollisionResult> retList;

		float maxOverLap = {};
		Math::Vector3 hitPos = {};

		for (const auto& obj : SceneManager::Instance().GetObjList())
		{
			if (obj->Intersects(ray, &retList))
			{

			}
		}
	}
}
