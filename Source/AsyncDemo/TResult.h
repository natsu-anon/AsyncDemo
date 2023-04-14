// Licensed under WTFPL v2

#pragma once

#include "CoreMinimal.h"

enum class EResolutionType : uint8
{
	FULL_RUN = 0,
	STOP_SIGNAL = 1 << 1
	// ADD MORE IF YOU NEED MORE!
};

template<typename T>
struct TResult
{
	EResolutionType ResolutionType;
	T Value;
};
