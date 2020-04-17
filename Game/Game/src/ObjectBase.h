#pragma once
# include "Common.hpp"

class ObjectBase
{
public:
	ObjectBase()
		: _handle(_handleForSetting)
		, _dispPriority(0)
	{
		++_handleForSetting;
	};

	ObjectBase(const int32& dispPriority)
		: _handle(_handleForSetting)
		, _dispPriority(dispPriority)
	{
		++_handleForSetting;
	};

	virtual void draw() {};

	const uint32 _handle;
	int32 _dispPriority;	// âÊñ ï\é¶ÇÃóDêÊìx
private:
	static uint32 _handleForSetting;
};