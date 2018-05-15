#ifndef API_H
#define API_H

#include <mutex>
#include <thread>
#include <vector>
#include <sstream>

#include "random.h"
#include "racer.h"

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
	 * @brief Creates the API for the racing game.
	 *
	 *  For now, mostly just creates a random number generator.
	 */
	void create();
	

    
    /**
	 * @brief Race a player
     * 
     * Simply locks the mountain and unlocks it.
	 */
	void race(Racer* racer);

    /**
	 * @brief Print the mountain to the console.
	 */
	void printMountain();
};

#endif /* API_H */
