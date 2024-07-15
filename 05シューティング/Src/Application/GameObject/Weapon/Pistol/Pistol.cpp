#include "Pistol.h"

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
