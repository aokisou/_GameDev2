#include "Lift.h"

void Lift::Update()
{
	float _sin = sin(DirectX::XMConvertToRadians(m_angle));

	++m_angle;
	if (m_angle >= 360.0f)
	{
		m_angle -= 360.0f;
	}

	Math::Matrix _transMat = Math::Matrix::CreateTranslation(_sin * m_moveVal, 10.0f, 60.0f);
	
	Math::Matrix _rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	m_mWorld = _rotMat * _transMat;
}

void Lift::Init()
{
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Models/Terrains/Lift/Lift.gltf");

	m_objName = "Lift";

	Math::Matrix _transMat = Math::Matrix::CreateTranslation(0, 15.f, -15.f);

	Math::Matrix _rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));

	m_mLocalCamera = _rotMat * _transMat;
}

void Lift::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}