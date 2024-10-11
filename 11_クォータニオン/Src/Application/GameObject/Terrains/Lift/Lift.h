#pragma once

class Lift : public KdGameObject
{
public :

	Lift() {}
	~Lift() override {}
	
	void Update() override;

	void Init() override;
	void DrawLit() override;

private :

	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	// 回転角度
	float m_angle = 0.0f;

	// 移動速度
	const float m_moveVal = 30.0f;
};
