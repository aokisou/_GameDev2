#include "Pistol.h"

#include "../../../Scene/SceneManager.h"
#include "../../Effect/Explosion/Explosion.h"

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
	if (m_bShot)
	{
		if (!m_wpParent.expired())
		{
			const std::shared_ptr<const KdGameObject> parent = m_wpParent.lock();
			KdCollider::RayInfo ray;
			ray.m_pos = parent->GetPos();
			ray.m_dir = parent->GetMatrix().Backward();
			//ray.m_dir = Math::Vector3::TransformNormal(Math::Vector3::Backward, parent->GetMatrix());
			ray.m_range = 1000.f;
			ray.m_type = KdCollider::Type::TypeDamage;

			float maxOverLap = 0.f;
			Math::Vector3 hitPos = Math::Vector3::Zero;
			bool isHit = false;

			for (const auto& obj : SceneManager::Instance().GetObjList())
			{
				std::list<KdCollider::CollisionResult> retList;

				if (obj->Intersects(ray, &retList))
				{
					for (const auto& ret : retList)
					{
						if (maxOverLap < ret.m_overlapDistance)
						{
							maxOverLap = ret.m_overlapDistance;
							hitPos = ret.m_hitPos;
							isHit = true;
						}
					}
				}
			}

			if (m_bRayBullet)
			{
				if (isHit)
				{
					std::shared_ptr<Explosion> exp = std::make_shared<Explosion>();
					exp->Init();
					exp->SetPos(hitPos);
					SceneManager::Instance().AddObject(exp);
				}
			}
		}

		m_bShot = false;
		m_bRayBullet = false;
	}

	WeaponBase::Update();
}

void Pistol::ShotBullet(const bool _bRay)
{
	//発射フラグ
	m_bShot = true;

	//弾とするか
	m_bRayBullet = _bRay;
}
