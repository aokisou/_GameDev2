#pragma once

class Lift :public KdGameObject
{
public:
	Lift(){}
	~Lift()override{}

	void Init()override;
	void Update()override;
	bool IsRideable()const override { return true; }
	void DrawLit()			override;

private:
	float m_moveVal = 30;
	float m_degAng = 0;
	std::shared_ptr<KdModelWork> m_spModel = nullptr;
};