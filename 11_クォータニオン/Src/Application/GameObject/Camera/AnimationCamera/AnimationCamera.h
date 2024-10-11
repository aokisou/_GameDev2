#pragma once

class GameScene;

class AnimationCamera :public KdGameObject
{
public:
	AnimationCamera() {}
	~AnimationCamera()override {}

	void Update()override;
	void Init()override;

	void SetAnimationInfo(GameScene* _owner, const std::shared_ptr<KdGameObject>& _startObj, const std::shared_ptr<KdGameObject>& _endObj, const float& _speed = 0.01f);

private:
	GameScene* m_owner;
	std::weak_ptr<KdGameObject> m_wpStart;
	std::weak_ptr<KdGameObject> m_wpEnd;

	// 進行度
	float m_progress = 0.f;

	float m_speed = 0.01f;
};