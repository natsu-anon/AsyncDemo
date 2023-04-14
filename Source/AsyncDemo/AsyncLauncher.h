// Licensed under WTFPL v2

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsyncLauncher.generated.h"

UCLASS()
class ASYNCDEMO_API AAsyncLauncher : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAsyncLauncher();

protected:

	class FRunnableStep1* Step1;
	class FRunnableStep2* Step2;
	class FRunnableStep3* Step3;
	class FRunnableStep4* Step4;

public:

	virtual void BeginDestroy() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void RunStep1();

	UFUNCTION(BlueprintCallable)
	virtual void RunStep2(int NumTimesToRun);

	UFUNCTION(BlueprintCallable)
	virtual void BasicPromiseExample();

	UFUNCTION(BlueprintCallable)
	virtual void ChainedPromiseExample();

	UFUNCTION(BlueprintCallable)
	virtual void RunStep3();

	UFUNCTION(BlueprintCallable)
	virtual void RunStep4();

};
