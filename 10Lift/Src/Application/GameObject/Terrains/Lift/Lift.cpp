#include "Lift.h"

void Lift::Init()
{
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Models/Terrains/Lift/Lift.gltf");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Lift", m_spModel, KdCollider::Type::TypeGround);

	m_mWorld.Translation({ 0,10,30 });
	m_moveVal = 30;
}

void Lift::Update()
{
	m_degAng++;
	if (m_degAng > 360)
	{
		m_degAng -= 360;
	}
	float move = sin(DirectX::XMConvertToRadians(m_degAng)) * m_moveVal;
	Math::Vector3 pos = m_mWorld.Translation();
	pos.x = move;
	m_mWorld.Translation(pos);
}

void Lift::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}
