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
	m_mWorld = Math::Matrix::CreateScale(10) * m_rotateMat * transMat;
}

void Bullet::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void Bullet::Shot(const Math::Vector3& _pos, const Math::Vector3& _dir)
{
	m_pos = _pos;
	m_dir = _dir;
	m_dir.Normalize();

	Math::Vector3 vecA = m_mWorld.Backward();
	vecA.Normalize();

	Math::Vector3 vecB = m_dir;
	vecB.Normalize();

	//内積
	//回転する角度
	float d = vecA.Dot(vecB);
	float ang = acos(d);

	//外積
	//回転するためのベクトル
	Math::Vector3 rotAxis = vecA.Cross(vecB);

	//内積で出した角度分、外積で出したベクトル方向に回転する
	m_rotateMat = Math::Matrix::CreateFromAxisAngle(rotAxis, ang);
}
