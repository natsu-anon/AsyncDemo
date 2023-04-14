// Licensed under WTFPL v2

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"

/**
 *
 */
class ASYNCDEMO_API FRunnableStep1 : FRunnable
{
public:
	FRunnableStep1();
	virtual ~FRunnableStep1();

private:

	FRunnableThread* Thread;

public:

	virtual void Exit() override;
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
};
