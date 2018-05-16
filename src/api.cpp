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
	: entities()
	, isWon(false)
{}

API::~API()
{}

void API::run()
{
	create();
	
	int roundCount = 1;
	
    while(!isWon) {
		cout << "-----------------------------------" << endl;
		cout << "-- ROUND #" << roundCount++ << endl;
		for(int i = 0; i < RACER_COUNT; ++i) {
			Racer* racer = &racers[i];
			racerThreads[i] = thread( [this, racer] { this->race(racer); } );
		}
		
		for(int i = 0; i < RACER_COUNT; ++i)
			racerThreads[i].join();
    }
}



void API::race(Racer* racer)
{
	this->planetXMutex.lock();
	
	if(isWon) {
		this->planetXMutex.unlock();
		return;
	}
	
	// Make move
	randomlyMoveRacer(racer);
	
    // Print move info
	cout << "-----------------------------" << endl;
    cout << racer->getId() << " has moved!" << endl;
	printRacerPositions();
	printPlanetX();
	
	Entity* e = getEntityAt(racer->getX(), racer->getY());
	if(e != NULL) {
		switch(e->getId().front())
		{
			case 'F':
				if(racer->hasCarrot()) {
					cout << racer->getId() << " has won!" << endl;
					isWon = true;
				}
				break;
			
			case 'C':
				if(racer->hasCarrot())
					break;
				removeEntity(e);
				racer->setHasCarrot(true);
				cout << racer->getId() << " has taken a carrot!" << endl;
				break;
				
			default:
				break;
		}
	}
		
	sleep_for(100ms); // Let user read this turn before unlocking
    this->planetXMutex.unlock();
}


void API::create()
{
	// Create racers
	racers[0] = Racer("B");
	racers[0].create();
	
	racers[1] = Racer("D");
	racers[1].create();
	
	racers[2] = Racer("T");
	racers[2].create();
	
	racers[3] = Racer("M");
	racers[3].create();
	
	
	// Create entities
	entities.reserve(3);
	
	entities.push_back(Entity("C"));
	entities[0].create();
	
	entities.push_back(Entity("C"));
	entities[1].create();
	
	entities.push_back(Entity("F"));
	entities[2].create();

	
	// Randomly place racers and entities
	randomizeRacers();
	randomizeEntities();
}


void API::randomizeEntities()
{	
	for(unsigned i = 0; i < entities.size(); ++i)
		randomizeEntity(&entities[i]);
}

void API::randomizeEntity(Entity* e)
{
	Entity* other;
	int randX;
	int randY;
	do {
		e->randomPosition(0, PLANETX_SIZE-1);
		randX = e->getX();
		randY = e->getY();
		
		e->setPos(-1,-1);
		other = getEntityAt(randX, randY);
		
		e->setPos(randX, randY);
	} while ( other != NULL );
}


Entity* API::getEntityAt(int x, int y)
{
	for(unsigned i = 0; i < entities.size(); ++i)
		if (entities[i].at(x,y))
			return &entities[i];
	
	return getRacerAt(x, y);
}


void API::removeEntity(Entity* e)
{
	for (vector<Entity>::iterator it = entities.begin() ; it != entities.end(); ++it)
	{
		if ( (e->getId() == (*it).getId())
		     &&	 (e->getX() == (*it).getX())
		     &&	 (e->getY() == (*it).getY())
		   )
		{
			it = entities.erase(it);
		}
	}
}


void API::randomizeRacers()
{	
	for(int i = 0; i < RACER_COUNT; ++i)
		randomizeRacer(&racers[i]);
}

void API::randomizeRacer(Racer* racer)
{
	Entity* other;
	do {
		racer->randomPosition(0, PLANETX_SIZE-1);
		other = getEntityAt(racer->getX(), racer->getY());
	} while ( other != NULL && racer->getId() != other->getId() );
}


void API::randomlyMoveRacer(Racer* racer)
{ 	
	int racerX = racer->getX();
	int racerY = racer->getY();	
	Racer* other;
	
	do {
		racer->randomlyMove(PLANETX_SIZE);
		other = getRacerAt(racer->getX(), racer->getY());
		if(other != NULL && racer->getId() != other->getId() ) racer->setPos(racerX, racerY);
	} while (other != NULL && racer->getId() != other->getId() );
}

Racer* API::getRacerAt(int x, int y)
{
	for(int i = 0; i < RACER_COUNT; ++i)
		if (racers[i].at(x,y))
			return &racers[i];
	
	return NULL;
}


void API::printPlanetX()
{
	for (int i = 0; i < PLANETX_SIZE; ++i)
	{
		for (int j = 0; j < PLANETX_SIZE; ++j)
		{
			Entity* e = getEntityAt(i,j);
			Racer* r = getRacerAt(i,j);
			if (r != NULL) {
				cout << r->getId();
				if (r->hasCarrot()) cout << "C";
				else cout << " ";
		    } else if (e != NULL) {
				cout << e->getId() << " ";
			} else {
				cout << "- ";
			}
		}
		
		cout << endl;
	}	
}


void API::printRacerPositions()
{
	for(unsigned i = 0; i < entities.size(); ++i)
		cout << entities[i].getId()
			 << ": ("
			 << entities[i].getX()
			 << ", "
			 << entities[i].getY()
			 << ")"
			 << endl;
	
	for(int i = 0; i < RACER_COUNT; ++i)
		cout << racers[i].getId()
			 << ": ("
			 << racers[i].getX()
			 << ", "
			 << racers[i].getY()
			 << ")"
			 << endl;
}
