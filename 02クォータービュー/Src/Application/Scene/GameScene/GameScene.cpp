#include "GameScene.h"
#include"../SceneManager.h"
#include "../../Object/BackGround/BackGround.h"

void GameScene::Event()
{

}

void GameScene::Init()
{
	m_camera = std::make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(60);

	std::shared_ptr<BackGround> obj;
	obj = std::make_shared<BackGround>();
	AddObject(obj);
}
