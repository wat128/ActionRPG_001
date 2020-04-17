#pragma once
# include "Common.hpp"

static uint32 handleForSetting = 0;

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
	int32 _dispPriority;	// âÊñ ï\é¶ÇÃóDêÊìx
};