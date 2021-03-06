#pragma once
# include "Common.hpp"

static uint32 handleForSetting = 1;

class ObjectBase
{
public:
	ObjectBase()
		: _handle(handleForSetting)
		, _dispPriority(0)
	{
		++handleForSetting;
	};

	ObjectBase(const int32& dispPriority)
		: _handle(handleForSetting)
		, _dispPriority(dispPriority)
	{
		++handleForSetting;
	};

	virtual void draw() {};

	const uint32 _handle;
	int32 _dispPriority;	// 画面表示の優先度
};