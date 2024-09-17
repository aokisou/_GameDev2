#pragma once

class Player;

class Cloud :public KdGameObject
{
public:
	Cloud(){}
	~Cloud()override{}

	void Init()				override;
	void Update()override;
	void DrawUnLit()			override;

	void SetPlayer(const std::shared_ptr<Player>& _player) { m_wpPlayer = _player; }

private:
	std::weak_ptr<Player> m_wpPlayer;
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;
};