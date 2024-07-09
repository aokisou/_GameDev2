#pragma once

class CameraBase;

class Player:public KdGameObject
{
public:
	Player(){}
	~Player()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;

	void SetCamera(std::shared_ptr<CameraBase> _spCamera) { m_wpCamera = _spCamera; }
private:
	Math::Vector3 m_pos = {};
	Math::Vector3 m_moveDir = {};
	const float m_movePow = 0.3f;

	std::weak_ptr<CameraBase> m_wpCamera;
};