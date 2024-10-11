#pragma once

#include"../BaseScene/BaseScene.h"

class CameraBase;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

	bool SetCameraTarget(const std::shared_ptr<KdGameObject>& _target);

private:
	std::string m_strCameraTarget = "Robot";
	std::weak_ptr<CameraBase> m_wpCamera;

	void ChangeCameraTarget();

	// 指定された名前で検索して合致したオブジェクトを返す
	const std::shared_ptr<KdGameObject>& FindObjectWithName(const std::string& _name);

	void Event() override;
	void Init() override;
};
