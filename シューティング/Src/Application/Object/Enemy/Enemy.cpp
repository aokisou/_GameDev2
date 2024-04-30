#include "Enemy.h"

void Enemy::Update()
{
	m_pos += m_movePow;

	if (m_pos.y < -360.f)
	{
		m_pos.y = 360.f;
	}

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Enemy::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);
	rc = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 64, 64, &rc);
}

void Enemy::OnHit()
{
	m_bAlive = false;
}

void Enemy::Init()
{
	m_tex.Load("Asset/Textures/enemy.png");
	m_pos = {};
	m_movePow = { 0.f,-2.f,0.f };
	m_mat = Math::Matrix::Identity;
	m_objType = ObjectType::Enemy;
}

void Enemy::Release()
{
}
