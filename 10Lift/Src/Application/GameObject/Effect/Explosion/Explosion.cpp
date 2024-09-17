#include "Explosion.h"

#include "../../../Scene/SceneManager.h"

void Explosion::Update()
{
	// アニメーション更新
	m_polygon.SetUVRect((int)m_animeCnt);	// UV座標を設定
	m_animeCnt += m_animeSpeed;				// カウント更新

	// アニメーションが終了したら消滅　※リストから除外
	if (m_animeCnt >= 8)
	{
		m_isExpired = true;
	}
}

void Explosion::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Explosion::Init()
{
	// 板ポリにテクスチャ(マテリアル)をロード
	m_polygon.SetMaterial("Asset/Textures/Explosion.png");

	// アニメーション分割数：横, 縦
	m_polygon.SetSplit(8, 1);

	// アニメーション初期値
	m_animeCnt = 0;
	m_animeSpeed = 1.0f;

	// 単位行列
	m_mWorld = Math::Matrix::CreateScale(2.0f);
}
