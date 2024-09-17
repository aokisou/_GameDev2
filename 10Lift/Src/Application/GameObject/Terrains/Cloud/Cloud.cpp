#include "Cloud.h"

#include "../../Character/Player/Player.h"

void Cloud::Init()
{
	m_spPoly = std::make_shared<KdSquarePolygon>();
	m_spPoly->SetMaterial("Asset/Textures/Cloud.png");
}

void Cloud::Update()
{
	const std::shared_ptr<Player> player = m_wpPlayer.lock();
	//Math::Vector3 pos = GetPos();
	//if (player)
	//{
	//	Math::Vector3 degAng = player->GetRotateDegAng();

	//	m_mWorld = Math::Matrix::CreateFromYawPitchRoll(
	//		DirectX::XMConvertToRadians(degAng.y),
	//		DirectX::XMConvertToRadians(degAng.x),
	//		DirectX::XMConvertToRadians(degAng.z));
	//}

	//m_mWorld.Translation(pos);

	Math::Matrix playerMat;
	if(player)
	{
		playerMat = player->GetMatrix();
		//m_mWorld = Math::Matrix::CreateWorld(GetPos(), playerMat.Backward(), playerMat.Up());
	}

	m_mWorld.Backward(playerMat.Backward());
	m_mWorld.Up(playerMat.Up());
	m_mWorld.Right(playerMat.Right());
}

void Cloud::DrawUnLit()
{
	//加算半透明
	KdShaderManager::Instance().ChangeBlendState(KdBlendState::Add);
	if (m_spPoly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
	}
	//半透明合成に戻す
	KdShaderManager::Instance().ChangeBlendState(KdBlendState::Alpha);

	//半透明問題
	//半透明にするオブジェクトは最後に描画しないと、透過部分が描画順の問題でバグる
	//解決策としてはZソートで奥から順番に描画するように設計する
	
	//①不透明なオブジェクトを描画する
	//②半透明オブジェクト(Zソート済み)を描画する
}
