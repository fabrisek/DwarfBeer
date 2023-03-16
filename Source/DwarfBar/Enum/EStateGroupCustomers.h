#pragma once
UENUM(BlueprintType)
enum class EStateGroupCustomers : uint8
{
	WalkToDoor,
	WaitTable,
	WalkToTable,
	WaitDrink,
	Drink,
	WalkToExit
};