#pragma once

class Ground : public KdGameObject
{
public:

	Ground() {}
	virtual ~Ground() override {}

	void Init() override;
	void DrawLit() override;

private:

	std::shared_ptr<KdModelWork> m_spModel = nullptr;
};
