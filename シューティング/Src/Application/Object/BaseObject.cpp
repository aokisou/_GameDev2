#include "BaseObject.h"

void BaseObject::Update()
{
}

void BaseObject::Draw()
{
}

void BaseObject::Init()
{
}

void BaseObject::Release()
{
}

void BaseObject::SetTexture(std::string _filename)
{
	m_tex.Load(_filename);
}

void BaseObject::OnHit()
{
}
