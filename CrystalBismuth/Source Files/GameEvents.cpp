#include "GameEvents.h"

ChickenClickEvent::ChickenClickEvent(Chicken* ckn, MouseAction button)
	: GameEvent(CHICKEN_CLICK_EVENT)
{
	mChicken = ckn;
	mMouseAction = button;
}

ResearchAddEvent::ResearchAddEvent(int amount)
	: GameEvent(RESEARCH_ADD_EVENT)
{
	mAmount = amount;
}