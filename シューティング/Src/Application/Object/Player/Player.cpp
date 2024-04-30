#include "Player.h"
#include "../../Scene/GameScene.h"
#include "../Bullet/Bullet.h"

void Player::Update()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 5.0f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 5.0f;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += 5.0f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= 5.0f;
	}

	m_shotInterval++;
	if (m_shotInterval > 10)
	{
		m_shotInterval -= 10;
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			std::shared_ptr<Bullet> b = std::make_shared<Bullet>();
			b->SetPos({ m_pos.x,m_pos.y });
			b->SetOwner(m_owner);
			m_owner->AddObjectList(b);
		}
	}

	//プレイヤーと敵の当たり判定
	//オブジェクトリストを全て見ていく
	for (auto& obj : m_owner->GetObjList())
	{
		//自分自身とは当たり判定しない
		if (obj->GetObjType() == ObjectType::Player) { continue; }
		//敵だったら当たり判定を行う
		if (obj->GetObjType() == ObjectType::Enemy)
		{
			//対象座標 - 自分座標 = 対象のベクトル
			Math::Vector3 v;
			v = obj->GetPos() - GetPos();

			//球判定
			if (v.Length() < 64.0f)
			{
				obj->OnHit();
			}
		}
	}

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Player::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, 64, 64, &rc);
}

void Player::Init()
{
	m_tex.Load("Asset/Textures/player.png");
	m_pos = {};						//0,0で初期化
	m_mat = Math::Matrix::Identity;	//単位行列で初期化
	//単位行列…拡大率すべて1.0f,他の値は全て0
	m_shotInterval = 0;
	m_objType = ObjectType::Player;
}

void Player::Release()
{
	//テクスチャはKdTexture型のデストラクタで
	//自動開放
}