#ifndef API_H
#define API_H

#include "planetx.h"

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
