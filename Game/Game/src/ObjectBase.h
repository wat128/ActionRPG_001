#pragma once
# include "Common.hpp"

class ObjectBase
{
public:
	ObjectBase() : _dispPriority(0)
	{};

	ObjectBase(const int32 dispPriority) : _dispPriority(dispPriority)
	{};

	virtual void draw() {};

	int32 _dispPriority;	// 画面表示の優先度
};