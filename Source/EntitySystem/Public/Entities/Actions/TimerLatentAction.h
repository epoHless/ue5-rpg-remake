#pragma once
#include <LatentActions.h>

class TimerLatentAction : public FPendingLatentAction
{
	int id;
	float MaxDuration;
	float& DeltaTime;
	float CurrentDuration;
	
public:

	TimerLatentAction(int id, float maxDuration, float& deltaTime):
	id(id), MaxDuration((maxDuration)), DeltaTime(deltaTime), CurrentDuration(0.f){}
	
	virtual void UpdateOperation(FLatentResponse& Response) override
	{
		CurrentDuration += DeltaTime;
		Response.DoneIf(CurrentDuration >= MaxDuration);
	}
};
