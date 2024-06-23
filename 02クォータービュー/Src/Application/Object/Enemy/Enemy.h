#pragma once

class Player;

class Enemy :public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy()override {}

	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void SetTarget(std::weak_ptr<Player> _target);

	void OnHit()override { m_isExpired = true; }
private:
	void Init()override;

	Math::Vector3 m_pos;
	//方向ベクトル
	Math::Vector3 m_dir;
	//力ベクトル
	float m_spd = 0.0f;
	float m_gravity = 0.0f;

	float m_animeCnt = 0;
	float m_animeSpeed = 0;

	std::shared_ptr<KdSquarePolygon> m_spPolygon;

	std::weak_ptr<Player> m_wpPlayer;
	bool m_bChase = false;
	float m_searchArea;
};