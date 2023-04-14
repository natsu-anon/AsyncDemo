// Licensed under WTFPL v2

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "../TResult.h"

/**
 *
 */
class ASYNCDEMO_API FRunnableStep4 : FRunnable
{
public:
	FRunnableStep4(class TPromise<TResult<TArray<int>>>* Promise);
	virtual ~FRunnableStep4();

protected:

	bool bStop;
	FRunnableThread* Thread;
	class TPromise<TResult<TArray<int>>>* Promise;

public:

	virtual void Exit() override;
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
};
