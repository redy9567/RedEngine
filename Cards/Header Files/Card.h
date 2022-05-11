#include "Unit.h"

enum Suit
{
	Clubs,
	Diamonds,
	Hearts,
	Spades,
	Joker
};

enum Value
{
	A = 1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	J,
	Q,
	K
};



class Card : public Unit
{

public:
	Card();
	Card(Vector2D);
	Card(Suit, Value, Vector2D);
	~Card();

private:
	Suit mSuit;
	Value mValue;

	bool faceDown;

};