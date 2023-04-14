// Licensed under WTFPL v2

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"

/**
 *
 */
class ASYNCDEMO_API FRunnableStep2 : FRunnable
{
public:
	FRunnableStep2(int NumTimesToRun);
	virtual ~FRunnableStep2();

protected:

	bool bStop;
	int NumTimesToRun;
	FRunnableThread* Thread;

public:

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
};
