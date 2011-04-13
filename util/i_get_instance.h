#pragma once

namespace util
{

template <class T>
class IGetInstance
{
protected:
	IGetInstance() {}

public:
	virtual ~IGetInstance() {}
	static T& GetInstance();
};

#include "i_get_instance.inl"

}