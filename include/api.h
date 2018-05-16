#ifndef API_H
#define API_H

#include <mutex>
#include <thread>
#include <vector>
#include <sstream>

#include "racer.h"
#include "entity.h"
#include "constants.h"

using namespace std;


/**
 * @brief Racing Game API class.
 * 
 * Simply call run and this API will play our racing game.
 */
class API
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
    vector<Entity> entities; 
  
    Racer racers[RACER_COUNT];
	thread racerThreads[RACER_COUNT];
    
    mutex planetXMutex;

	bool isWon;

	/**
	 * @brief Creates the API for the racing game.
	 *
	 *  For now, mostly just creates a random number generator.
	 */
	void create();
    
    
    void randomizeEntities();
    void randomizeEntity(Entity*);
    Entity* getEntityAt(int, int);
    void removeEntity(Entity*);
    
    void randomizeRacers();
    void randomizeRacer(Racer*);
    void randomlyMoveRacer(Racer*);
    Racer* getRacerAt(int, int);
    
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
