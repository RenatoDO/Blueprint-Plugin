// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlueNoiseBPLibrary.h"
#include "BlueNoise.h"
#include "Kismet/KismetMathLibrary.h"

UBlueNoiseBPLibrary::UBlueNoiseBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UBlueNoiseBPLibrary::BlueNoiseSampleFunction(float Param)
{
	return -1;
}

FVector UBlueNoiseBPLibrary::CreateRandomVector(UPARAM(ref)FRandomStream& Stream, float Min, float Max)
{
	float RandX = UKismetMathLibrary::RandomFloatInRangeFromStream(Min, Max, Stream);
	float RandY = UKismetMathLibrary::RandomFloatInRangeFromStream(Min, Max, Stream);

	return FVector(RandX, RandY, 0.f);
}

void UBlueNoiseBPLibrary::InitLocationContainer(UPARAM(ref)FNoiseData& LocationContainer, int32 Seed)
{
	UKismetMathLibrary::SetRandomStreamSeed(LocationContainer.RandomStream, Seed);
}

void UBlueNoiseBPLibrary::AddLocationToNoiseData(UPARAM(ref)FNoiseData& NoiseData, FVector Location)
{
	NoiseData.GeneratedPoints.Add(Location);
}

FVector UBlueNoiseBPLibrary::MakeRandomPointInRange(UPARAM(ref)FNoiseData& NoiseData, float Min, float Max)
{
	if (NoiseData.GeneratedPoints.Num() < 1) return CreateRandomVector(NoiseData.RandomStream, Min, Max);

	TArray<FVector> Candidates;
	Candidates.Init(FVector(), 5 * NoiseData.GeneratedPoints.Num());


	float MaxDistance = 0.f;
	FVector BestCandidate = FVector();
	for (FVector& i : Candidates)
	{
		i = CreateRandomVector(NoiseData.RandomStream, Min, Max);

		float MinDistance = FindDistance(i, NoiseData.GeneratedPoints[0]);
		for (FVector GeneratedPoint : NoiseData.GeneratedPoints)
		{
			if (FindDistance(i, GeneratedPoint) < MinDistance) MinDistance = FindDistance(i, GeneratedPoint);
		}

		if (MinDistance > MaxDistance)
		{
			MaxDistance = MinDistance;
			BestCandidate = i;
		}
	}
	return BestCandidate;
}

float UBlueNoiseBPLibrary::FindDistance(FVector& Vector1, FVector& Vector2)
{
	float dx = UKismetMathLibrary::Abs(Vector2.X - Vector1.X);
	float dy = UKismetMathLibrary::Abs(Vector2.Y - Vector1.Y);

	if (dx > 0.5f) dx = 1.0f - dx;

	if (dy > 0.5f) dy = 1.0f - dy;

	return UKismetMathLibrary::Sqrt(dx * dx + dy * dy);
}