#include "WeaponBase.h"

void WeaponBase::Update()
{
	Math::Matrix parentMat = {};
	if (!m_wpParent.expired())
	{
		parentMat = m_wpParent.lock()->GetMatrix();
	}

	m_mWorld = m_localMat * parentMat;
}

void WeaponBase::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}
