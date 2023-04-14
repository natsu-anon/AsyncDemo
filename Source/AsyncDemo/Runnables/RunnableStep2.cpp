// Licensed under WTFPL v2

#include "RunnableStep2.h"

FRunnableStep2::FRunnableStep2(int NumTimesToRun)
{
	this->NumTimesToRun = NumTimesToRun;
	Thread = FRunnableThread::Create(this, TEXT("Step 2"));
}

FRunnableStep2::~FRunnableStep2()
{
	if (Thread)
	{
		Thread->Kill();
		delete Thread;
	}
}

bool FRunnableStep2::Init()
{
	bStop = false;
	return true;
}

uint32 FRunnableStep2::Run()
{
	for (int i = 0; i < NumTimesToRun; i++)
	{
		if (bStop)
		{
			UE_LOG(LogTemp, Warning, TEXT("Step 2: STOPPED!"))
			return 1;
		}
		UE_LOG(LogTemp, Display, TEXT("Step 2: This code is running for the %d-th time ASYNCHRONOUSLY!"), i + 1)
		FPlatformProcess::Sleep(1.0f);
	}
	return 0;
}

// called by Thread->Kill()
void FRunnableStep2::Stop()
{
	bStop = true;
}
