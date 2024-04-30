#pragma once

#include "../BaseObject.h"

class Enemy :public BaseObject
{
public:
	Enemy() { Init(); }
	~Enemy() { Release(); }

	void Update()override;
	void Draw()override;

	void OnHit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetPos(Math::Vector2 _pos) { m_pos = { _pos.x,_pos.y,0.f }; }//SetPosのオーバーロード

	void SetMove(Math::Vector3 _movePow) { m_movePow = _movePow; }

private:
	void Init()override;
	void Release()override;

	Math::Vector3 m_movePow;
};