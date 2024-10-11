#pragma once

class Torii : public KdGameObject
{
public:

	Torii() {}
	virtual ~Torii() override {}

	void Init() override;
	void DrawLit() override;

private:

	std::shared_ptr<KdModelWork> m_spModel = nullptr;
};
