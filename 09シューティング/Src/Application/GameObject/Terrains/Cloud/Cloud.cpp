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

void Cloud::DrawLit()
{
	if (m_spPoly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
	}
}
