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
	PlanetX planetX;
};

#endif /* API_H */
