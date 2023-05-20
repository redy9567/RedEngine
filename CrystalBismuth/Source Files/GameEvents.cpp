#include "GameEvents.h"

ChickenClickEvent::ChickenClickEvent(Chicken* ckn, MouseAction button)
	: GameEvent(CHICKEN_CLICK_EVENT)
{
	mChicken = ckn;
	mMouseAction = button;
}