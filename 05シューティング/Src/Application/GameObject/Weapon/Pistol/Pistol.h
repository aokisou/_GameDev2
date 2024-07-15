#pragma once

#include "../WeaponBase/WeaponBase.h"

class Pistol :public WeaponBase
{
public:
	Pistol(){}
	~Pistol()override{}

	void Init()override;
	void Update()override;
};