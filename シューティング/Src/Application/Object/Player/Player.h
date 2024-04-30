#pragma once

//基本的にヘッダーファイルの中で
//別のヘッダーファイルをインクルードするのはNG
//継承元クラスのヘッダーのみインクルードが必要なので可とする
#include "../BaseObject.h"

class GameScene;

class Player :public BaseObject
{
public:
	Player() { Init(); }
	~Player() { Release(); }

	//基底クラスの仮想関数をオーバーライド
	//override指定子はなくてもオーバーライドはされるが
	//override可能か判別する目的でもある(可読性の問題でつけるべき)
	void Update()override;
	void Draw()override;

	void SetOwner(GameScene* _owner) { m_owner = _owner; }

private:
	void Init()override;
	void Release()override;

	int m_shotInterval = 0;

	GameScene* m_owner;
};