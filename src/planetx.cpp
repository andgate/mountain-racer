#include "api.h"

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "racer.h"
#include "constants.h"

using namespace std::this_thread;     // sleep_for
using namespace std::chrono_literals; // ns, ms, s


PlanetX::PlanetX()
	: entities()
	, m_isWon(false)
    , m_roundCount(1)
{}

PlanetX::~PlanetX()
{}

bool PlanetX::isWon()
{
	return m_isWon;
}


int PlanetX::roundCount()
{
	return m_roundCount;
}

void PlanetX::create()
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
	
	entities.push_back(Entity("F"));
	entities[0].create();
	
	entities.push_back(Entity("C"));
	entities[1].create();
	
	entities.push_back(Entity("C"));
	entities[2].create();

	
	// Randomly place racers and entities
	randomizeRacers();
	randomizeAllEntities();
}


void PlanetX::step()
{
	cout << "-----------------------------------" << endl;
	cout << "-- ROUND #" << roundCount << endl;
	
	// Marvin is th last racer in our list.
	int marvinId = RACER_COUNT - 1;
	
	// Iterate through racers up to marvin.
	for(int i = 0; i < marvinId; ++i) {
		Racer* racer = &racers[i];
		racerThreads[i] = thread( [this, racer] { this->race(racer); } );
	}
	
	// Race marvin
	racerThreads[marvinId] = thread( [this] { this->raceMarvin(); } );
	
	// Wait for all the racers to finish.
	for(int i = 0; i < RACER_COUNT; ++i)
		racerThreads[i].join();
	
	// Marvin randomly moves the mountain every three turns.
	// if((roundCount-1)%3)
	// then randomlyMoveMountain();
	
	++roundCount;
}


void PlanetX::randomizeAllEntities()
{	
	for(unsigned i = 0; i < entities.size(); ++i)
		randomizeEntity(&entities[i]);
	
	for(int i = 0; i < RACER_COUNT; ++i)
		randomizeEntity(&racers[i]);
}

void PlanetX::randomizeEntity(Entity* e)
{
	Entity* other;
	Position randPos;
	
	do {
		randPos = e->randomPosition(0, PLANETX_SIZE-1);
		other = getEntityAt(randX, randY);
		
		// If spot is empty, set as entity position
		if(other != null)
			e->setPos(randPos.getX(), randPos.getY());
	} while ( other != NULL );
}

/*
void PlanetX::randomizeRacer(Racer* racer)
{
	Entity* other;
	Position randPos;
	do {
		randPos = racer->randomPosition(0, PLANETX_SIZE-1);
		other = getEntityAt(randPos->getX(), randPos->getY());
		
		// If spot is empty, set as entity position
		if(other != null)
			e->setPos(randPos.getX(), randPos.getY());
		
	} while ( other != NULL );
}
*/

// Race method ran by racer thread
void PlanetX::race(Racer* racer)
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


void PlanetX::randomlyMoveRacer(Racer* racer)
{ 	
	int racerX = racer->getX();
	int racerY = racer->getY();	
	Racer* other;
	Position randPos;
	do {
		randPos = racer->randomDirection();
		randPos.add(racer->getPos());
		other = getRacerAt(racer->getX(), racer->getY());
		if(other == NULL)
	} while (other != NULL && racer->getId() != other->getId() );
	
	racer->setPos(randPos);
}



void PlanetX::raceMarvin()
{
	int marvinId = RACER_COUNT - 1;
	Racer* racer = racers[marvinId];
	this->planetXMutex.lock();
	
	if(isWon) {
		this->planetXMutex.unlock();
		return;
	}
	
	// Make move
	randomlyMoveMarvin();
	
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

void PlanetX::randomlyMoveMarvin()
{ 	
	int marvinId = RACER_COUNT-1;
	Racer* racer = racers[marvinId];
	
	int racerX = racer->getX();
	int racerY = racer->getY();	
	Racer* other;
	
	do {
		racer->randomlyMove(PLANETX_SIZE);
		other = getRacerAt(racer->getX(), racer->getY());
		if( other != NULL && (other->getId() == "F") )
			racer->setPos(racerX, racerY);
	} while ( other != NULL && (other->getId() == "F") );
}


Entity* PlanetX::getEntityAt(int x, int y)
{
	for(unsigned i = 0; i < entities.size(); ++i)
		if (entities[i].at(x,y))
			return &entities[i];
	
	return getRacerAt(x, y);
}


void PlanetX::removeEntity(Entity* e)
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



Racer* PlanetX::getRacerAt(int x, int y)
{
	for(int i = 0; i < RACER_COUNT; ++i)
		if (racers[i].at(x,y))
			return &racers[i];
	
	return NULL;
}

void PlanetX::removeRacer(Racer* racer)
{
	vector tmp = vectpr(racers[i]);
	
	
	for (vector<Entity>::iterator it = tmp.begin() ; it != tmp.end(); ++it)
	{
		if ( (racer->getId() == (*it).getId())
		     &&	 (racer->getX() == (*it).getX())
		     &&	 (racer->getY() == (*it).getY())
		   )
		{
			it = entities.erase(it);
		}
	}
	
	racers = tmp;
}


void PlanetX::printPlanetX()
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


void PlanetX::printRacerPositions()
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
