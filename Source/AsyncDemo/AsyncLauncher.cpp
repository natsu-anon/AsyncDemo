// Licensed under WTFPL v2

#include "AsyncLauncher.h"
#include "HAL/Runnable.h"
#include "Async/Future.h"
#include "TResult.h"
#include "Runnables/RunnableStep1.h"
#include "Runnables/RunnableStep2.h"
#include "Runnables/RunnableStep3.h"
#include "Runnables/RunnableStep4.h"

// Sets default values
AAsyncLauncher::AAsyncLauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Step1 = nullptr;
	Step2 = nullptr;
	Step3 = nullptr;
	Step4 = nullptr;
}

void AAsyncLauncher::BeginDestroy()
{
	if (Step1)
	{
		delete Step1;
		Step1 = nullptr;
	}
	if (Step2)
	{
		delete Step2;
		Step2 = nullptr;
	}
	if (Step3)
	{
		delete Step3;
		Step3 = nullptr;
	}
	if (Step4)
	{
		delete Step4;
		Step4 = nullptr;
	}
	Super::BeginDestroy();
}

// Called every frame
void AAsyncLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAsyncLauncher::RunStep1()
{
	Step1 = new FRunnableStep1();
}

void AAsyncLauncher::RunStep2(int NumTimesToRun)
{
	Step2 = new FRunnableStep2(NumTimesToRun);
}

void AAsyncLauncher::BasicPromiseExample()
{
	TPromise<int>* Promise = new TPromise<int>();
	Promise->GetFuture().Next([](int Result)
	{
		UE_LOG(LogTemp, Warning, TEXT("Basic Promise Example Result: %d"), Result)
	});
	Promise->SetValue(2 + 2);
	delete Promise; // NOTE: CAN'T DELETE CAPTURED POINTERS INSIDE OF LAMBDAS
}

void AAsyncLauncher::ChainedPromiseExample()
{
	TPromise<int>* PromiseA = new TPromise<int>();
	TPromise<int>* PromiseB = new TPromise<int>();
	PromiseA->GetFuture().Next([PromiseB](int Result)
	{
		UE_LOG(LogTemp, Warning, TEXT("Promise A Result: %d"), Result)
		return PromiseB->GetFuture().Get();
	})
	.Next([&PromiseA, &PromiseB](int Result) mutable // you CAN delete pointers inside of lambda functions this way
	{
		UE_LOG(LogTemp, Warning, TEXT("Promise B Result: %d"), Result)
		delete PromiseA;
		delete PromiseB;
	});
	PromiseB->SetValue(22);
	PromiseA->SetValue(2 + 2);
}

void AAsyncLauncher::RunStep3()
{
	TPromise<TArray<int>>* Promise = new TPromise<TArray<int>>();
	Promise->GetFuture().Next([](TArray<int> PrimeNumbers)
	{
		// You should do something more interesting here
		UE_LOG(LogTemp, Warning, TEXT("Step 3 Result: There are %d primes between 2 & 10000000!"), PrimeNumbers.Num())
		//Promise = nullptr;
	});
	Step3 = new FRunnableStep3(Promise);
}

void AAsyncLauncher::RunStep4()
{
	TPromise<TResult<TArray<int>>>* Promise = new TPromise<TResult<TArray<int>>>();
	Promise->GetFuture().Next([](TResult<TArray<int>> Res)
	{
		if (Res.ResolutionType == EResolutionType::FULL_RUN)
		{
			// You should do something more interesting here
			UE_LOG(LogTemp, Warning, TEXT("Step 4 Result: There are %d primes between 2 & 10000000!"), Res.Value.Num())
		}
		else // gets called if stoppped early
		{
			UE_LOG(LogTemp, Warning, TEXT("Stopped Step 4 before completion :("))
		}
		//Promise = nullptr;
	});
	Step4 = new FRunnableStep4(Promise);
}

