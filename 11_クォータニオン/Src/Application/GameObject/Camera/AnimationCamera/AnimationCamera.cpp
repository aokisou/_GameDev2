#include "AnimationCamera.h"

#include "../../../Scene/GameScene/GameScene.h"

void AnimationCamera::Update()
{
	const std::shared_ptr<KdGameObject> start = m_wpStart.lock();
	const std::shared_ptr<KdGameObject> end = m_wpEnd.lock();
	if (!start || !end) 
	{
		m_isExpired = true;
		return;
	}

	Math::Matrix startMat = start->GetCameraMatrix();
	Math::Matrix endMat = end->GetCameraMatrix();

	Math::Quaternion startQuater = Math::Quaternion::CreateFromRotationMatrix(startMat);
	Math::Quaternion endQuater = Math::Quaternion::CreateFromRotationMatrix(endMat);

	// 球面線形補完
	Math::Quaternion nowQuater = Math::Quaternion::Slerp(startQuater, endQuater, m_progress);

	m_mWorld = Math::Matrix::CreateFromQuaternion(nowQuater);

	Math::Vector3 startVec;
	Math::Vector3 endVec;

	startVec = startMat.Translation();
	endVec = endMat.Translation();

	Math::Vector3 nowVec;

	nowVec = Math::Vector3::Lerp(startVec, endVec, m_progress);

	m_mWorld.Translation(nowVec);

	m_progress += m_speed;
	if (m_progress > 1.0f)
	{
		m_progress = 1.0f;
		m_isExpired = true;
		if (m_owner)
		{
			m_owner->SetCameraTarget(end);
		}
	}
}

void AnimationCamera::Init()
{
	m_objName = "AnimationCamera";
}

void AnimationCamera::SetAnimationInfo(GameScene* _owner, const std::shared_ptr<KdGameObject>& _startObj, const std::shared_ptr<KdGameObject>& _endObj, const float& _speed)
{
	m_owner = _owner;
	m_wpStart = _startObj;
	m_wpEnd = _endObj;

	m_progress = 0.0f;
	m_speed = _speed;
}
