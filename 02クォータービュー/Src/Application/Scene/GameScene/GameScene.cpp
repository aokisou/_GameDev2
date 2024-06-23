#include "GameScene.h"

#include"../SceneManager.h"
#include "../../Object/BackGround/BackGround.h"
#include "../../Object/Ground/Ground.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"

void GameScene::Event()
{
	Math::Matrix transMat, rotateXMat,plyMat;
	transMat = Math::Matrix::CreateTranslation(0, 3, -3);
	rotateXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));
	plyMat = Math::Matrix::Identity;
	if (!m_wpPlayer.expired())
	{
		plyMat = m_wpPlayer.lock()->GetMatrix();
	}
	m_camera->SetCameraMatrix(rotateXMat * transMat * plyMat);
}

void GameScene::Init()
{
	m_camera = std::make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(60);

	std::shared_ptr<BackGround> bgrd;
	bgrd = std::make_shared<BackGround>();
	AddObject(bgrd);

	std::shared_ptr<Ground> grd;
	grd = std::make_shared<Ground>();
	AddObject(grd);

	std::shared_ptr<Player> ply;
	ply = std::make_shared<Player>();
	AddObject(ply);
	m_wpPlayer = ply;

	std::shared_ptr<Enemy> emy;
	for (int i = 0; i < 20; i++)
	{
		emy = std::make_shared<Enemy>();
		emy->SetPos(Math::Vector3(i * 10 - 50.0f, 0, 20.0f));
		emy->SetTarget(ply);
		AddObject(emy);
	}
}
