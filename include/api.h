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
    
    const int RACER_COUNT = 4;
    Racer* racers[4];
	thread racerThreads[4];
    
    const int PLANETX_SIZE = 10;
    mutex planetXMutex;

	bool isWon;

	/**
	 * @brief Creates the API for the racing game.
	 *
	 *  For now, mostly just creates a random number generator.
	 */
	void create();
    
    
    void randomizeRacers();
    void randomizeRacer(Racer*);
    void randomlyMoveRacer(Racer*);
    Racer* getRacerAt(int atX, int atY);
    
    /**
	 * @brief Race a player
     *
     * Simply locks the mountain and unlocks it.
	 */
	void race(Racer* racer);

    /**
	 * @brief Print Planet X to the console.
	 */
	void printPlanetX();
    
    void printRacerPositions();
};

#endif /* API_H */
