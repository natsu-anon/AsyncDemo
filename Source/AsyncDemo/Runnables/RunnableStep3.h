// Licensed under WTFPL v2

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"

/**
 *
 */
class ASYNCDEMO_API FRunnableStep3 : FRunnable
{
public:
	FRunnableStep3(TPromise<TArray<int>>* Promise);
	virtual ~FRunnableStep3();

protected:

	bool bStop;
	FRunnableThread* Thread;
	class TPromise<TArray<int>>* Promise;

public:

	virtual void Exit() override;
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
};
