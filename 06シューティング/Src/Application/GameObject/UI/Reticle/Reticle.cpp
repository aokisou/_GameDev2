#include "Reticle.h"

void Reticle::Init()
{
	m_spTex = std::make_shared<KdTexture>();
	m_spTex->Load("Asset/Textures/Reticle.png");
}

void Reticle::DrawSprite()
{
	if (m_spTex)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spTex,0,0);
	}
}
