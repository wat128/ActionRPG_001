# pragma once
# include "../Common.hpp"

// �͂��܂�̋u�R�i�K�� / ����
class Map01_2 : public MyApp::Scene
{
private:

public:

	Map01_2(const InitData& init);

	void update() override;

	void draw() const override;
};
