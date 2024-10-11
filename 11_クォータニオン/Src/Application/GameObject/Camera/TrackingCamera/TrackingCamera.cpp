#include "TrackingCamera.h"

void TrackingCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	//// 基準点(ターゲット)からどれだけ離れているか
	//m_mLocalPos = Math::Matrix::CreateTranslation(0, 5.0f, -5.0f);

	//// どれだけ傾けているか
	//m_mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
}

void TrackingCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = _spTarget->GetCameraMatrix();
	}

	m_mWorld = _targetMat;

	CameraBase::Update();
}
