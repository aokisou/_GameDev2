#include "Bullet.h"

void Bullet::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Bullet/Arrow.gltf");

	m_mWorld = Math::Matrix::CreateScale(10);
}

void Bullet::Update()
{
	m_pos += m_dir * m_speed;

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Math::Matrix::CreateScale(10) * transMat;
}

void Bullet::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}
