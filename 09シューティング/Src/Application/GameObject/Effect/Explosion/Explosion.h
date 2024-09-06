#pragma once

class Explosion : public KdGameObject
{
public :

	Explosion() {}
	~Explosion() override {}

	void Update() override;

	void DrawUnLit() override;

	void Init() override;

private :

	KdSquarePolygon m_polygon;

	// アニメーション情報
	float m_animeCnt = 0.0f;
	float m_animeSpeed = 0.0f;
};
