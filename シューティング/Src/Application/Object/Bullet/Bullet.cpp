#include "Bullet.h"
#include "../../Scene/GameScene.h"

void Bullet::Update()
{
	m_pos += m_movePow;

	for (auto obj : m_owner->GetObjList())
	{
		if (obj->GetObjType() == ObjectType::Enemy)
		{
			Math::Vector3 v;
			v = obj->GetPos() - GetPos();

			if (v.Length() < 40.0f)
			{
				OnHit();
				obj->OnHit();
			}
		}
	}

	if (m_pos.y > 640)
	{
		m_bAlive = false;
	}

	m_mat = Math::Matrix::CreateTranslation(m_pos);
}

void Bullet::Draw()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle src = { 0,0,13,37 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, &src);
}

void Bullet::OnHit()
{
	m_bAlive = false;
}

void Bullet::Init()
{
	m_pos = {};						//0,0で初期化
	m_movePow = { 0.0f,10.0f,0.0f };
	m_mat = Math::Matrix::Identity;	//単位行列で初期化
	m_objType = ObjectType::Bullet;
	m_tex.Load("Asset/Textures/Bullet.png");
}

void Bullet::Release()
{
}