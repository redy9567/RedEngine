#include "Card.h"
#include "Game.h"
#include "GraphicsBufferManager.h"

Card::Card()
{
	mSuit = Suit::Spades;
	mValue = Value::A;

	mVisual.sprite = Game::getInstance()->mpGraphicsBufferManager->getGraphicsBuffer()
}