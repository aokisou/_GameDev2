#pragma once

class BaseObject
{
public:
	BaseObject(){}
	virtual ~BaseObject() { Release(); }

	//オブジェクトの種類
	enum class ObjectType
	{
		Player,
		Enemy,
		Bullet
	};

	//仮想関数
	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void Release();

	//ヒット時の処理
	virtual void OnHit();

	void SetTexture(std::string _filename);

	ObjectType GetObjType() { return m_objType; }

	Math::Vector3 GetPos() { return m_pos; }

	bool GetAlive() { return m_bAlive; }

protected:
	KdTexture		m_tex;

	Math::Vector3	m_pos;
	Math::Matrix	m_mat;

	bool			m_bAlive = true;

	ObjectType		m_objType;
private:
};