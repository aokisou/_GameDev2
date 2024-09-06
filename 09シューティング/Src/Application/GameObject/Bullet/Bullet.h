#pragma once

class Bullet :public KdGameObject
{
public:
	Bullet(){}
	~Bullet()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;

	void Shot(const Math::Vector3& _pos, const Math::Vector3& _dir);

private:
	std::shared_ptr<KdModelData> m_spModel = {};

	Math::Vector3 m_pos = Math::Vector3::Zero;
	Math::Vector3 m_dir = Math::Vector3::Zero;
	float m_speed = 0.6f;

	Math::Matrix m_rotateMat;
};