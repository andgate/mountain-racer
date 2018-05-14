#ifndef API_H
#define API_H

#include <thread>
#include <vector>
#include <sstream>

#include "random.h"
#include "player.h"
#include "table.h"

using namespace std;


void race()
{
	return;
}

/**
 * @brief Racing Game API class.
 * 
 * Simply call run and this API will play our racing game.
 */
class API : Random
{
public:
	/**
	 * @brief Default constructor
	 */
	API();

	/**
	 * @brief Default destructor
	 */
	~API();

	/**
	 * @brief Runs through our racegame.
	 * 
	 * @return EXIT_SUCCESS when successful, otherwise EXIT_FAILURE.
	 */
	int run();

private:
	thread bunny  (race);
	thread taz    (race);
	thread tweety (race);
	thread marvin (race);

	static const int PLAYER_COUNT = 2;
	static const int INITIAL_HAND_SIZE = 10;

	Table table;
	
	vector<Player> players;

	int currPlayerIndex = 0;
	int turnCount = 0;

	/**
	 * @brief Creates the API for dominos.
	 *
	 *  Creates random number generator, table, and players.
	 */
	void create();
	
	/**
	 * @brief Creates some number of players.
	 *
	 *  Players willed be named "Player1", "Player2", etc.
	 *
	 * @param playerCount number of players to create.
	 */
	void createPlayers(int playerCount);

	/**
	 * @brief Create a single player.
	 *
	 * @param playerName Name to give player.
	 */
	void createPlayer(string playerName);
    

	/**
	 * @brief Randomly decides which player goes first.
	 */
	void pickFirstTurn();

	/**
	 * @brief Gives each player an amount dominoes.
	 *
	 * @param amount Number of dominos each player may recieve.
	 */
	void deal(int amount);

	/**
	 * @brief A standard turn
	 * 
	 * Takes a random domino from the player's hand and plays it
	 * 
	 * @return True when the current player has won.
	 */
	bool playTurn();

	/**
	 * @brief Changes whose turn it is
	 * 
	 * @return Player* 
	 */
	Player* nextPlayer();

	/**
	 * @brief Get the Current Player object
	 * 
	 * @return Player* 
	 */
	Player* getCurrentPlayer();

	/**
	 * @brief Checks if the players are blocked
	 * 
	 * @return True when blocked, false otherwise.
	 */
	bool isBlocked();

	/**
	 * @brief Prints all player's hands
	 * 
	 */
	void printPlayersHands();

	/**
	 * @brief Print ranking of players to the console.
	 * 
	 */
	void printRanking();
};

#endif /* API_H */
