# pragma once
# include "../Common.hpp"

// はじまりの丘３段階目 / 小屋
class Map01_3 : public MyApp::Scene
{
private:

public:

	Map01_3(const InitData& init);

	void update() override;

	void draw() const override;
};
