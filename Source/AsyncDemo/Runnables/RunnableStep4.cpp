// Licensed under WTFPL v2

#include "RunnableStep4.h"
#include "Async/Future.h"

#define TOO_FAST

FRunnableStep4::FRunnableStep4(TPromise<TResult<TArray<int>>>* Promise)
{
	this->Promise = Promise;
	Thread = FRunnableThread::Create(this, TEXT("Step 4"));
}

FRunnableStep4::~FRunnableStep4()
{
	if (Thread)
	{
		Thread->Kill();
		delete Thread;
	}
}

void FRunnableStep4::Exit()
{
	delete Promise;
	UE_LOG(LogTemp, Warning, TEXT("Promise FINALLY deleted in FRunnableStep4::Exit()"))
}

bool FRunnableStep4::Init()
{
	bStop = false;
	return true;
}

// use this to double check: https://t5k.org/howmany.html
uint32 FRunnableStep4::Run()
{
	UE_LOG(LogTemp, Warning, TEXT("Running Step 4--this WILL take some time"))
	bool bPrime;
	TArray<int> PrimeNumbers = TArray<int>();
	for (int i = 2; i <= 10000000; i++)
	{
		int j = 2;
		bPrime = true;
		while (j * j <= i)
		{
			if (bStop)
			{
				UE_LOG(LogTemp, Warning, TEXT("Stopped Step 4"))
				Promise->SetValue(TResult<TArray<int>>{ EResolutionType::STOP_SIGNAL });
				#ifdef TOO_FAST
				FPlatformProcess::Sleep(1.0f;)
				#endif
				return 1;
			}
			if (i % j == 0)
			{
				bPrime = false;
				break;
			}
			j++;
		}
		if (bPrime)
		{
			PrimeNumbers.Add(i);
		}
	}
	Promise->SetValue(TResult<TArray<int>>{ EResolutionType::FULL_RUN, PrimeNumbers });
	#ifdef TOO_FAST
	FPlatformProcess::Sleep(1.0f;)
	#endif
	return 0;
}

void FRunnableStep4::Stop()
{
	bStop = true;
}
