#ifndef API_H
#define API_H

#include <mutex>
#include <thread>
#include <vector>
#include <sstream>

#include "random.h"

using namespace std;


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
	void run();

private:
	thread bunny;
	thread taz;
	thread tweety;
	thread marvin;
    
    mutex mountainMutex;
    vector<vector<int>> mountain;

	bool isWon;

	/**
	 * @brief Creates the API for dominos.
	 *
	 *  Creates random number generator, table, and players.
	 */
	void create();
	

	/**
	 * @brief A standard turn
  
	 * Takes a random domino from the player's hand and plays it
	 * 
	 * @return True when the current player has won.
	 */
	void race();

    /**
	 * @brief Print ranking of players to the console.
	 * 
	 */
	void printMountain();
};

#endif /* API_H */
