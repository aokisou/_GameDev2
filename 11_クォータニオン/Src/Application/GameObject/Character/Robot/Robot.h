#pragma once

class Robot : public KdGameObject
{
public :

	Robot() {}
	~Robot() override {}

	void Init() override;
	void DrawLit() override;

private :

	std::shared_ptr<KdModelWork> m_spModel = nullptr;
};
