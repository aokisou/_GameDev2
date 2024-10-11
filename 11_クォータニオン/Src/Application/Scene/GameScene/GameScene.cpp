#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Camera/TrackingCamera/TrackingCamera.h"
#include "../../GameObject/Character/Robot/Robot.h"
#include "../../GameObject/Terrains/Ground/Ground.h"
#include "../../GameObject/Terrains/Torii/Torii.h"
#include "../../GameObject/Terrains/Lift/Lift.h"
#include "../../GameObject/Camera/AnimationCamera/AnimationCamera.h"

bool GameScene::SetCameraTarget(const std::shared_ptr<KdGameObject>& _target)
{
	if (!_target) { return false; }

	const std::shared_ptr<CameraBase>& camera = m_wpCamera.lock();
	if (camera)
	{
		camera->SetTarget(_target);
		return true;
	}

	return false;
}

void GameScene::ChangeCameraTarget()
{
	if (FindObjectWithName("AnimationCamera")) { return; }

	std::shared_ptr<KdGameObject> now = FindObjectWithName(m_strCameraTarget);
	if (m_strCameraTarget == "Robot")
	{
		m_strCameraTarget = "Torii";
	}
	else if (m_strCameraTarget == "Torii")
	{
		m_strCameraTarget = "Lift";
	}
	else
	{
		m_strCameraTarget = "Robot";
	}
	std::shared_ptr<KdGameObject> target = FindObjectWithName(m_strCameraTarget);
	if (!target) { return; }

	//std::shared_ptr<CameraBase> camera = m_wpCamera.lock();
	//if (camera)
	//{
	//	camera->SetTarget(target);
	//}

	std::shared_ptr<AnimationCamera> animeCamera = std::make_shared<AnimationCamera>();
	animeCamera->Init();
	animeCamera->SetAnimationInfo(this, now, target);
	animeCamera->Update();
	AddObject(animeCamera);

	std::shared_ptr<CameraBase> camera = m_wpCamera.lock();
	if (camera)
	{
		camera->SetTarget(animeCamera);
	}
}

const std::shared_ptr<KdGameObject>& GameScene::FindObjectWithName(const std::string& _name)
{
	for (const auto& obj : m_objList)
	{
		if (obj->GetObjName() == _name)
		{
			return obj;
		}
	}

	return nullptr;
}

void GameScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		ChangeCameraTarget();
	}
}

void GameScene::Init()
{
	// カーソルを非表示
	ShowCursor(false);

	// 地形 地面
	std::shared_ptr<Ground> _ground = std::make_shared<Ground>();
	_ground->Init();
	m_objList.push_back(_ground);

	// 地形 地面
	std::shared_ptr<Torii> _torii = std::make_shared<Torii>();
	_torii->Init();
	m_objList.push_back(_torii);

	// リフト
	std::shared_ptr<Lift> _lift;
	_lift = std::make_shared<Lift>();
	_lift->Init();
	m_objList.push_back(_lift);

	// ロボット
	std::shared_ptr<Robot> _robot;
	_robot = std::make_shared<Robot>();
	_robot->Init();
	m_objList.push_back(_robot);
	
	// カメラ
	std::shared_ptr<TrackingCamera> _camera = std::make_shared<TrackingCamera>();
	_camera->Init();
	m_objList.push_back(_camera);

	// 必要なデータを渡しておく
	_camera->SetTarget(_robot);
	m_wpCamera = _camera;
}
