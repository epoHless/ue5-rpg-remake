#include "RoomManagement/Data/RoomInstance.h"

bool FRoomInstance::IsCompleted()
{
	for (int i = 0; i < Entities.Num(); i++)
	{
		if(Entities[i].bActive) return false;
	}
		
	return true;
}
