#pragma once

class BackGround : public KdGameObject
{
public:
	BackGround() { Init(); }
	~BackGround()override {}

	void DrawUnLit()override;

private:
	void Init()override;

	KdSquarePolygon m_polygon;
};