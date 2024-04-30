#pragma once

#include "../BaseObject.h"

class GameScene;

class Bullet :public BaseObject
{
public:
	Bullet() { Init(); }
	~Bullet() { Release(); }

	void Update()override;
	void Draw()override;
	void SetOwner(GameScene* _owner) { m_owner = _owner; }

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetPos(Math::Vector2 _pos) { m_pos = { _pos.x,_pos.y,0.f }; }//SetPosのオーバーロード

	void OnHit();

private:
	void Init()override;
	void Release()override;

	Math::Vector3 m_movePow;

	GameScene* m_owner;
};