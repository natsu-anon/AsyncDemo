// Licensed under WTFPL v2


#include "RunnableStep3.h"
#include "Async/Future.h"

FRunnableStep3::FRunnableStep3(TPromise<TArray<int>>* Promise)
{
	this->Promise = Promise;
	Thread = FRunnableThread::Create(this, TEXT("Step 3"));
}

FRunnableStep3::~FRunnableStep3()
{
	if (Thread)
	{
		Thread->Kill();
		delete Thread;
	}
}

void FRunnableStep3::Exit()
{
	delete Promise;
	UE_LOG(LogTemp, Warning, TEXT("Promise FINALLY deleted in FRunnableStep3::Exit()"));
}

bool FRunnableStep3::Init()
{
	bStop = false;
	return true;
}

// yeah, just let it rock.  No sleep.
// use this to double check: https://t5k.org/howmany.html
uint32 FRunnableStep3::Run()
{
	UE_LOG(LogTemp, Warning, TEXT("Running Step 3--this WILL take some time"))
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
				UE_LOG(LogTemp, Warning, TEXT("Stopped Step 3"))
				Promise->SetValue(TArray<int>());
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
	Promise->SetValue(PrimeNumbers);
	return 0;
}

void FRunnableStep3::Stop()
{
	bStop = true;
}
