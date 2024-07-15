#pragma once

class WoddenBox :public KdGameObject
{
public:
	WoddenBox(){}
	~WoddenBox()override{}

	void Init()				override;
	void DrawLit()			override;

private:
	std::shared_ptr<KdModelWork> m_spModel = nullptr;
};