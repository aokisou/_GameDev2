#include "Robot.h"

void Robot::Init()
{
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Models/Character/Robot/Robot.gltf");

	m_objName = "Robot";

	Math::Matrix _transMat = Math::Matrix::CreateTranslation(0, 5.f, -5.f);

	Math::Matrix _rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));

	m_mLocalCamera = _rotMat * _transMat;
}

void Robot::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
