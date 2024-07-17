#pragma once

class WeaponBase :public KdGameObject
{
public:
	WeaponBase(){}
	virtual ~WeaponBase()override{}

	virtual void Update()override;
	void DrawLit()override;

	virtual void ShotBullet(const bool _bRay = false) = 0;

	void SetParent(const std::weak_ptr<KdGameObject>& _parent) { m_wpParent = _parent; }

protected:
	std::shared_ptr<KdModelWork> m_spModel = {};

	std::weak_ptr<KdGameObject> m_wpParent;

	Math::Matrix m_localMat = {};

	//弾発射
	bool m_bShot = {};
	
	bool m_bRayBullet = {};
};