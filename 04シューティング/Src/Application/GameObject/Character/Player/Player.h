#pragma once

class CameraBase;

class Player:public KdGameObject
{
public:
	Player(){}
	~Player()override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;

	//void SetCamera(std::shared_ptr<CameraBase> _spCamera) { m_wpCamera = _spCamera; }
private:
	void UpdateRotateByMouse();

	const Math::Matrix GetRotationMatrix()const
	{
		return Math::Matrix::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(m_degAng.y),
			DirectX::XMConvertToRadians(m_degAng.x),
			DirectX::XMConvertToRadians(m_degAng.z));
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY(
			DirectX::XMConvertToRadians(m_degAng.y));
	}

	Math::Vector3 m_pos = {};
	Math::Vector3 m_degAng = {};
	Math::Vector3 m_moveDir = {};
	const float m_movePow = 0.3f;
	const float m_adjustHeight = 10.0f;

	const float m_gravityPow = 0.04f;
	float m_gravity = {};

	POINT m_fixMousePos = {};

	//std::weak_ptr<CameraBase> m_wpCamera;
};