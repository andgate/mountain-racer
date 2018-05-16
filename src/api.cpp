#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "api.h"
#include "racer.h"

using namespace std::this_thread;     // sleep_for
using namespace std::chrono_literals; // ns, ms, s


API::API()
	: isWon(false)
{
	racers[0] = new Racer("B");
	racers[1] = new Racer("D");
	racers[2] = new Racer("T");
	racers[3] = new Racer("M");
}

API::~API()
{
	for(int i = 0; i < RACER_COUNT; ++i)
		delete racers[i];
}

void API::run()
{
	create();
	
    while(!isWon) {
		for(int i = 0; i < RACER_COUNT; ++i)
			racerThreads[i] = thread( [this, i] { this->race(this->racers[i] ); } );
		
		for(int i = 0; i < RACER_COUNT; ++i)
			racerThreads[i].join();
    }
}

void API::create()
{
	Random::create();
	randomizeRacers();
}


void API::randomizeRacers()
{
	for(int i = 0; i < RACER_COUNT; ++i)
		racers[i]->getPos()->setPos(-1, -1);
	
	for(int i = 0; i < RACER_COUNT; ++i)
		randomizeRacer(racers[i]);
}

void API::randomizeRacer(Racer* racer)
{
	int x;
	int y;
	Racer* other;

	do {
		x = randomInt(0, PLANETX_SIZE-1);
		y = randomInt(0, PLANETX_SIZE-1);
		other = getRacerAt(x, y);
	} while (other != NULL);

	racer->getPos()->setPos(x, y);
}

void API::randomlyMoveRacer(Racer* racer)
{ 	
	int racerX = racer->getPos()->getX();
	int racerY = racer->getPos()->getY();
	
	int x;
	int y;
	Racer* other;
	
	do
	{
		int direction = randomInt(0, 3);
		
		switch(direction)
		{
			case 0:
				x = 0; y = -1; break; // Move up
			case 1:
				x = 0; y = 1; break; // Move down
			case 2:
				x = -1; y = 0; break; // Move left
			case 3:
				x = 1; y = 0; break; // Move right
			default:
				return;
		}
		
		x = x < 0 ? (x + racerX + PLANETX_SIZE) % PLANETX_SIZE
				  : (x + racerX) % PLANETX_SIZE; 
		y = y < 0 ? (y + racerY + PLANETX_SIZE) % PLANETX_SIZE
				  : (y + racerY) % PLANETX_SIZE;
		
		other = getRacerAt(x, y);
	} while (other != NULL);
	
	racer->getPos()->setPos(x, y);
}

Racer* API::getRacerAt(int x, int y)
{
	for(int i = 0; i < RACER_COUNT; ++i)
		if (racers[i]->getPos()->at(x,y))
			return racers[i];
	
	return NULL;
}


void API::race(Racer* racer)
{
	this->planetXMutex.lock();
    
	// Make move
	randomlyMoveRacer(racer);
	
    // Print move info
    cout << racer->getId() << " has moved!" << endl;
	printRacerPositions();
	printPlanetX();
	
	sleep_for(1s); // Let user read this turn before unlocking
    this->planetXMutex.unlock();
}


void API::printPlanetX()
{
	for (int i = 0; i < PLANETX_SIZE; ++i)
	{
		for (int j = 0; j < PLANETX_SIZE; ++j)
		{
			Racer* racer = getRacerAt(i,j);
			if (racer == NULL)
				cout << "-";
			else
				cout << racer->getId();
		}
		
		cout << endl;
	}	
}


void API::printRacerPositions()
{
	for(int i = 0; i < RACER_COUNT; ++i)
		cout << racers[i]->getId()
			 << ": ("
			 << racers[i]->getPos()->getX()
			 << ", "
			 << racers[i]->getPos()->getY()
			 << ")"
			 << endl;
}
