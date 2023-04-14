// Licensed under WTFPL v2

#include "RunnableStep1.h"

FRunnableStep1::FRunnableStep1()
{
	Thread = FRunnableThread::Create(this, TEXT("Step 1"));
}

FRunnableStep1::~FRunnableStep1()
{
	if (Thread)
	{
		Thread->Kill();
		delete Thread;
	}
}

void FRunnableStep1::Exit()
{
	// see: https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/HAL/FRunnable/Exit/
	// Called in the context of the aggregrating thread to perform any cleanup
}

bool FRunnableStep1::Init()
{
	return true;
}

uint32 FRunnableStep1::Run()
{
	while (true)
	{
		UE_LOG(LogTemp, Display, TEXT("Step 1: This code is running asynchronously!!"))
		FPlatformProcess::Sleep(1.0f);
	}
	return 0;
}

void FRunnableStep1::Stop()
{
	// gets called by Thread->Kill()
}
