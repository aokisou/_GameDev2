#include "GameScene.h"

#include"../SceneManager.h"
#include "../../main.h"
#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Terrains/Terrain/Terrain.h"
#include "../../GameObject/Character/Player/Player.h"
#include "../../GameObject/Terrains/WoodenBox/WoodenBox.h"
#include "../../GameObject/Weapon/Pistol/Pistol.h"
#include "../../GameObject/UI/Reticle/Reticle.h"
#include "../../GameObject/Terrains/Cloud/Cloud.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	ShowCursor(false);

	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	AddObject(player);

	std::shared_ptr<Terrain> terrain = std::make_shared<Terrain>();
	terrain->SetScale(3);
	terrain->Init();
	AddObject(terrain);

	std::shared_ptr<WoddenBox> box;
	for (int i = 0; i < 5; i++)
	{
		box = std::make_shared<WoddenBox>();
		box->SetPos({-60.0f + i * 30.0f, 0.0f, 50.0f});
		box->SetScale(10);
		box->Init();
		AddObject(box);
	}

	std::shared_ptr<Cloud> cloud;
	for (int i = 0; i < 5; i++)
	{
		cloud = std::make_shared<Cloud>();
		cloud->SetPos({ 0.0f, 10.0f, 2.0f * i });
		cloud->Init();
		cloud->SetPlayer(player);
		AddObject(cloud);
	}

	std::shared_ptr<Pistol> pistol = std::make_shared<Pistol>();
	pistol->Init();
	pistol->SetParent(player);
	AddObject(pistol);

	std::shared_ptr<Reticle> reticle = std::make_shared<Reticle>();
	reticle->Init();
	AddObject(reticle);

	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	AddObject(camera);

	//player->SetCamera(camera);
	camera->SetTarget(player);
	player->SetWeapon(pistol);
}
