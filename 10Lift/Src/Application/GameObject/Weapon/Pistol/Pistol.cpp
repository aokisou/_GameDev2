#include "Pistol.h"

#include "../../../Scene/SceneManager.h"
#include "../../Effect/Explosion/Explosion.h"
#include "../../Bullet/Bullet.h"

void Pistol::Init()
{
	std::shared_ptr<KdModelData> model = std::make_shared<KdModelData>();
	model->Load("Asset/Models/Weapon/Pistol/Pistol.gltf");
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData(model);

	m_localMat = Math::Matrix::CreateTranslation({0.35f,-0.25f,0.2f});

	//銃から銃口への行列
	//m_localMuzzleMat = Math::Matrix::CreateTranslation({ -0.2f,0.18f,0.7f }) * m_localMat;

	m_localMuzzleMat = m_spModel->FindNode("AttachPoint")->m_worldTransform * m_localMat;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Pistol::Update()
{
	if (!m_wpParent.expired())
	{
		const std::shared_ptr<const KdGameObject> parent = m_wpParent.lock();

		Math::Matrix muzzleMat;
		muzzleMat = m_localMuzzleMat * parent->GetMatrix();
		m_pDebugWire->AddDebugSphere(muzzleMat.Translation(), 0.05f, kBlueColor);

		if (m_bShot)
		{
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
			else
			{
				if (isHit)
				{
					std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();
					bullet->Init();
					Math::Vector3 dir = hitPos - muzzleMat.Translation();
					dir.Normalize();
					bullet->Shot(muzzleMat.Translation(), dir);
					SceneManager::Instance().AddObject(bullet);
				}
			}

			m_bShot = false;
			m_bRayBullet = false;
		}

		WeaponBase::Update();
	}
}

void Pistol::ShotBullet(const bool _bRay)
{
	//発射フラグ
	m_bShot = true;

	//弾とするか
	m_bRayBullet = _bRay;
}
