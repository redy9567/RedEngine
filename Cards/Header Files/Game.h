#pragma once
#include "Trackable.h"
#include "InputSystem.h"
#include <string>

class GraphicsSystem;
class InputSystem;
class Player;
class Timer;
class UnitManager;
class AnimationManager;
class GraphicsBufferManager;
class GameListener;
class EventSystem;
class Vector2D;

const std::string ASSET_PATH = GAMEASSETS; //MAKE THIS RELATIVE PATH
const std::string BACKGROUND_FILEPATH = "room/room0000.png";
const std::string CLUBS_ACE_FILEPATH = "cards/CA.png";
const std::string CLUBS_TWO_FILEPATH = "cards/C2.png";
const std::string CLUBS_THREE_FILEPATH = "cards/C3.png";
const std::string CLUBS_FOUR_FILEPATH = "cards/C4.png";
const std::string CLUBS_FIVE_FILEPATH = "cards/C5.png";
const std::string CLUBS_SIX_FILEPATH = "cards/C6.png";
const std::string CLUBS_SEVEN_FILEPATH = "cards/C7.png";
const std::string CLUBS_EIGHT_FILEPATH = "cards/C8.png";
const std::string CLUBS_NINE_FILEPATH = "cards/C9.png";
const std::string CLUBS_TEN_FILEPATH = "cards/C10.png";
const std::string CLUBS_JACK_FILEPATH = "cards/CJ.png";
const std::string CLUBS_QUEEN_FILEPATH = "cards/CQ.png";
const std::string CLUBS_KING_FILEPATH = "cards/CK.png";
const std::string DIAMONDS_ACE_FILEPATH = "cards/DA.png";
const std::string DIAMONDS_TWO_FILEPATH = "cards/D2.png";
const std::string DIAMONDS_THREE_FILEPATH = "cards/D3.png";
const std::string DIAMONDS_FOUR_FILEPATH = "cards/D4.png";
const std::string DIAMONDS_FIVE_FILEPATH = "cards/D5.png";
const std::string DIAMONDS_SIX_FILEPATH = "cards/D6.png";
const std::string DIAMONDS_SEVEN_FILEPATH = "cards/D7.png";
const std::string DIAMONDS_EIGHT_FILEPATH = "cards/D8.png";
const std::string DIAMONDS_NINE_FILEPATH = "cards/D9.png";
const std::string DIAMONDS_TEN_FILEPATH = "cards/D10.png";
const std::string DIAMONDS_JACK_FILEPATH = "cards/DJ.png";
const std::string DIAMONDS_QUEEN_FILEPATH = "cards/DQ.png";
const std::string DIAMONDS_KING_FILEPATH = "cards/DK.png";
const std::string HEARTS_ACE_FILEPATH = "cards/HA.png";
const std::string HEARTS_TWO_FILEPATH = "cards/H2.png";
const std::string HEARTS_THREE_FILEPATH = "cards/H3.png";
const std::string HEARTS_FOUR_FILEPATH = "cards/H4.png";
const std::string HEARTS_FIVE_FILEPATH = "cards/H5.png";
const std::string HEARTS_SIX_FILEPATH = "cards/H6.png";
const std::string HEARTS_SEVEN_FILEPATH = "cards/H7.png";
const std::string HEARTS_EIGHT_FILEPATH = "cards/H8.png";
const std::string HEARTS_NINE_FILEPATH = "cards/H9.png";
const std::string HEARTS_TEN_FILEPATH = "cards/H10.png";
const std::string HEARTS_JACK_FILEPATH = "cards/HJ.png";
const std::string HEARTS_QUEEN_FILEPATH = "cards/HQ.png";
const std::string HEARTS_KING_FILEPATH = "cards/HK.png";
const std::string SPADES_ACE_FILEPATH = "cards/SA.png";
const std::string SPADES_TWO_FILEPATH = "cards/S2.png";
const std::string SPADES_THREE_FILEPATH = "cards/S3.png";
const std::string SPADES_FOUR_FILEPATH = "cards/S4.png";
const std::string SPADES_FIVE_FILEPATH = "cards/S5.png";
const std::string SPADES_SIX_FILEPATH = "cards/S6.png";
const std::string SPADES_SEVEN_FILEPATH = "cards/S7.png";
const std::string SPADES_EIGHT_FILEPATH = "cards/S8.png";
const std::string SPADES_NINE_FILEPATH = "cards/S9.png";
const std::string SPADES_TEN_FILEPATH = "cards/S10.png";
const std::string SPADES_JACK_FILEPATH = "cards/SJ.png";
const std::string SPADES_QUEEN_FILEPATH = "cards/SQ.png";
const std::string SPADES_KING_FILEPATH = "cards/SK.png";
const std::string BLACK_JOKER_FILEPATH = "cards/JB.png";
const std::string RED_JOKER_FILEPATH = "cards/JR.png";
const std::string BACK_ONE_FILEPATH = "cards/Card-Back-01.png";
const std::string BACK_TWO_FILEPATH = "cards/Card-Back-02.png";
const std::string BACK_THREE_FILEPATH = "cards/Card-Back-03.png";
const std::string BACK_FOUR_FILEPATH = "cards/Card-Back-04.png";
const std::string BACK_FIVE_FILEPATH = "cards/Card-Back-05.png";
const std::string BACK_SIX_FILEPATH = "cards/Card-Back-06.png";


const float PROJECTILE_SPEED = 100.0f;

class Game : public Trackable
{
public:
	friend class GameListener;
	friend class Card;

	static Game* getInstance();
	static void cleanupInstance();

	void init(int screenWidth, int screenHeight, int fps = 60, bool debugMode = false);
	void cleanup();

	void startGame();

private:
	Game();
	~Game();

	void getInput();
	void update();
	void render();

	void debug(); //Just a bunch of stuff to do in Debug Mode

	void DPlayerMove(Vector2D loc); //Functions that begin with the prefix D are debug functions
	void DKeyPress(KeyCode);
	void DMousePress(int);
	void DKeyRelease(KeyCode);
	void DMouseRelease(int);

	void fireProj();

	void quitGame();

	//Init functions to break up large overall init function
	void initGraphicsBuffers();

	static Game* mspInstance;

	GraphicsSystem* mpGraphicsSystem;

	UnitManager* mpUnitManager;
	AnimationManager* mpAnimationManager;
	GraphicsBufferManager* mpGraphicsBufferManager;

	GameListener* mpGameListener;

	Player* mpPlayerUnit;

	Timer* mpGameTimer;

	double deltaTime;
	bool mDebugMode, mIsPlaying;

	float mTimePerFrame;
	
};
