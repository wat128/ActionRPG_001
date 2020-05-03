# pragma once
# include "../Common.hpp"

// はじまりの丘３段階目 / 外
class Map01_1 : public MyApp::Scene
{
private:

public:

	Map01_1(const InitData& init);

	void update() override;

	void draw() const override;
};