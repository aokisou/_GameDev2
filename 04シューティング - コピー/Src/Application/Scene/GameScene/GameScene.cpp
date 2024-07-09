#include "GameScene.h"

#include"../SceneManager.h"
#include "../../main.h"
#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Terrains/Terrain/Terrain.h"
#include "../../GameObject/Character/Player/Player.h"

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
	terrain->Init();
	AddObject(terrain);

	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	AddObject(camera);

	//player->SetCamera(camera);
	camera->SetTarget(player);
}
