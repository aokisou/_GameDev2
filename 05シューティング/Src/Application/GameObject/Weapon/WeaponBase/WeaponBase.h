#pragma once

class WeaponBase :public KdGameObject
{
public:
	WeaponBase(){}
	virtual ~WeaponBase()override{}

	virtual void Update()override;
	void DrawLit()override;

	void SetParent(const std::weak_ptr<KdGameObject>& _parent) { m_wpParent = _parent; }

protected:
	std::shared_ptr<KdModelWork> m_spModel = {};

	std::weak_ptr<KdGameObject> m_wpParent;

	Math::Matrix m_localMat = {};
};