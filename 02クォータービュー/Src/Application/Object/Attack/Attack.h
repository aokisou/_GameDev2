#pragma once

class Attack :public KdGameObject
{
public:
	Attack() { Init(); }
	~Attack(){}

	void Init()override;

	void Update()override;

	void DrawUnLit()override;

	void OnHit()override { m_isExpired = true; }
private:
	float m_animeCnt = 0;
	float m_animeSpeed = 0;

	float m_attackArea = 0;

	std::shared_ptr<KdSquarePolygon> m_spPolygon;
};