#pragma once

class Player :public KdGameObject
{
public:
	Player() { Init(); }
	~Player()override{}

	enum DirType
	{
		Up		= 1 << 0,//上
		Down	= 1 << 1,//下
		Left	= 1 << 2,//左
		Right	= 1 << 3,//右
	};

	struct AnimationInfo
	{
		int start = 0;
		int end = 0;
		float cnt = 0;
		float speed = 0;
	};

	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

private:
	void Init()override;
	void ChangeAnimation();

	Math::Vector3 m_pos = {};
	//方向ベクトル
	Math::Vector3 m_dir = {};
	//力ベクトル
	float m_spd = 0.0f;
	float m_gravity = 0.0f;

	Math::Vector3 m_attackDir = {};

	UINT m_dirType = DirType::Down;

	AnimationInfo m_animeInfo;

	std::shared_ptr<KdSquarePolygon> m_spPolygon;

	bool m_keyFlg = false;
};