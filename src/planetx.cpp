#include "planetx.h"


#include <chrono>
#include <iostream>

using namespace std::this_thread;     // sleep_for
using namespace std::chrono_literals; // ns, ms, s


PlanetX::PlanetX()
	: racers(RACER_COUNT)
	, entities(ENTITY_COUNT)
	, m_winnerName()
    , m_roundCount(1)
{}

PlanetX::~PlanetX()
{}

string PlanetX::getWinner()
{
	return m_winnerName;
}

bool PlanetX::isWon()
{
	return !m_winnerName.empty();
}


int PlanetX::roundCount()
{
	return m_roundCount;
}

void PlanetX::create()
{
	// Create racers
    racers.clear();
    racers.reserve(RACER_COUNT);
    
	racers.push_back(make_shared<Racer>("Bunny", "B"));
	racers[0]->create();
	
	racers.push_back(make_shared<Racer>("Taz", "D"));
	racers[1]->create();
	
	racers.push_back(make_shared<Racer>("Tweety", "T"));
	racers[2]->create();
	
    // Marvin is always at the last racer
	racers.push_back(make_shared<Racer>("Marvin", "M"));
	racers[3]->create();
	
    
    // Create entities
    entities.clear();
    entities.reserve(ENTITY_COUNT);
    
	entities.push_back(make_shared<Entity>("Mountain", "F"));
	entities[0]->create();
	
	entities.push_back(make_shared<Entity>("Carrot", "C"));
	entities[1]->create();
	
	entities.push_back(make_shared<Entity>("Carrot", "C"));
	entities[2]->create();

	
	// Randomly place racers and entities
	randomizeAllEntities();
}


void PlanetX::step()
{
	//cout << "-----------------------------------" << endl;
	//cout << "-- ROUND #" << m_roundCount << endl;

	int threadCount = racers.size();
	// Iterate through racers up to marvin.
	for(int i = 0; i < threadCount; ++i) {
		auto racer = racers[i];
		racerThreads[i] = thread( [this, racer] { this->race(racer); } );
	}
	
	// Wait for all the racers to finish.
	for(int i = 0; i < threadCount; ++i)
		racerThreads[i].join();
	
	// Marvin randomly moves the mountain every three turns.
	if ( (m_roundCount%3) == 0) randomlyMoveMountain();
	
	++m_roundCount;
}


void PlanetX::randomizeAllEntities()
{	
	for(unsigned i = 0; i < entities.size(); ++i)
		randomizeEntity(entities[i]);
	
	for(int i = 0; i < RACER_COUNT; ++i)
		randomizeEntity(racers[i]);
}


void PlanetX::randomizeEntity(shared_ptr<Entity> e)
{
	shared_ptr<Entity> other;
	Position randPos;
	
	do {
		randPos = e->randomPosition(0, PLANETX_SIZE-1);
		other = getAnyEntityAt(randPos);
	} while ( other != nullptr );
	
	e->setPos(randPos);
}

void PlanetX::randomlyMoveMountain()
{
	randomizeEntity(entities.front()); // Mountain is always at the front
	printPlanetX();
	printBorder();
}


// Race method ran by racer thread
void PlanetX::race(shared_ptr<Racer> racer)
{
	this->planetXMutex.lock();
	
	if(isWon() || racer == nullptr) {
		this->planetXMutex.unlock();
		return;
	}
	
    // Print move info
	//cout << "-----------------------------" << endl;
    //cout << racer->getId() << " has moved!" << endl;
	
	
	// The big block of game logic!
	bool hasMoved = false;
	while (!hasMoved)
	{
		randomlyMoveRacer(racer);
		
		auto e = getEntityAt(*racer);
		auto r = getRacerAt(*racer);
		if (e != nullptr)
		{
			switch (e->getId().front())
			{
				case 'C':
					if ( racer->hasCarrot() ) {
						racer->undoMove();					
					} else {
						removeEntity(e);
						racer->setHasCarrot(true);
						hasMoved = true;
					}
					break;
					
				case 'F':
					if ( racer->hasCarrot() ) {
						//removeEntity(e);
						m_winnerName = racer->getName();
						hasMoved = true;
					} else {
					    racer->undoMove();
					}
					break;
				
				default:
					racer->undoMove();
					break;
			}
		} else if (r != nullptr && r->getId() != racer->getId())
		{
			if(racer->getId().front() == 'M') {
				// Kill other, take their carrot, give it to marvin
				removeRacer(r);
				hasMoved = true;
				if (!racer->hasCarrot() && r->hasCarrot())
					racer->setHasCarrot(true);
			} else {
				racer->undoMove();
			}
		} else {
			hasMoved = true;
		}
	}
		
	printPlanetX();
	printBorder();

	sleep_for(300ms); // Let user read this turn before unlocking
    this->planetXMutex.unlock();
}


void PlanetX::randomlyMoveRacer(shared_ptr<Racer> racer)
{
	Position randPos = racer->randomDirection();
	
	int x = racer->getX() + randPos.getX();
	int y = racer->getY() + randPos.getY();
	
	x = ( (x % PLANETX_SIZE) + PLANETX_SIZE ) % PLANETX_SIZE;
	y = ( (y % PLANETX_SIZE) + PLANETX_SIZE ) % PLANETX_SIZE;
	
	racer->setPos(x, y);
}


// Helpers for entities and racers

shared_ptr<Entity> PlanetX::getAnyEntityAt(Position pos)
{
	return getAnyEntityAt(pos.getX(), pos.getY());
}

shared_ptr<Entity> PlanetX::getAnyEntityAt(int x, int y)
{
	auto e = getEntityAt(x, y);
	if(e != nullptr) return e;
	
	e = getRacerAt(x, y);
	if (e != nullptr) return e;
	
	return nullptr;
}


// Helpers for entities

shared_ptr<Entity> PlanetX::getEntityAt(Position pos)
{
	return getEntityAt(pos.getX(), pos.getY());
}

shared_ptr<Entity> PlanetX::getEntityAt(int x, int y)
{
	for(unsigned i = 0; i < entities.size(); ++i)
		if (entities[i]->at(x,y))
			return entities[i];
	
	return nullptr;
}

void PlanetX::removeEntity(shared_ptr<Entity> e)
{
	for (unsigned i = 0; i < entities.size(); ++i)
	{
		auto h = entities[i];
		
		if (    (e->getId() == h->getId())
		     && (e->getX()  == h->getX())
		     && (e->getY()  == h->getY())
		   )
		{
			entities.erase(entities.begin()+i);
			return;
		}
	}
}


// Helpers for Racers

shared_ptr<Racer> PlanetX::getRacerAt(Position pos)
{
	return getRacerAt(pos.getX(), pos.getY());
}

shared_ptr<Racer> PlanetX::getRacerAt(int x, int y)
{
	for(unsigned i = 0; i < racers.size(); ++i)
		if (racers[i]->at(x,y))
			return racers[i];
	
	return nullptr;
}

void PlanetX::removeRacer(shared_ptr<Racer> racer)
{	
	for (unsigned i = 0; i < racers.size(); ++i)
	{
		auto other = racers[i];
		
		if (    (racer->getId() == other->getId())
		     && (racer->getX()  == other->getX())
		     && (racer->getY()  == other->getY())
		   )
		{
			racers.erase(racers.begin()+i);
			return;
		}
	}
}


shared_ptr<Entity> PlanetX::collidesAnyEntity(shared_ptr<Entity> e)
{
	auto other = collidesEntity(e);
	if(other != nullptr) return other;
	
	other = collidesRacer(e);
	if (other != nullptr) return other;
	
	return nullptr;
}

shared_ptr<Entity> PlanetX::collidesEntity(shared_ptr<Entity> e)
{
	int x = e->getX();
	int y = e->getY();
	string id = e->getId();
	
	for(unsigned i = 0; i < entities.size(); ++i)
		if (entities[i]->at(x,y) && id != entities[i]->getId())
			return entities[i];
	
	return nullptr;
}


shared_ptr<Racer> PlanetX::collidesRacer(shared_ptr<Entity> r)
{
	int x = r->getX();
	int y = r->getY();
	string id = r->getId();
	
	for(int i = 0; i < RACER_COUNT; ++i)
		if (racers[i]->at(x,y) && racers[i]->getId() != id)
			return racers[i];
	
	return nullptr;
}


void PlanetX::printPlanetX()
{
	for (int i = 0; i < PLANETX_SIZE; ++i)
	{
		for (int j = 0; j < PLANETX_SIZE; ++j)
		{
			auto e = getEntityAt(i,j);
			auto r = getRacerAt(i,j);
			if (r != nullptr) {
				cout << "    "
					 << r->getId()
					 << (r->hasCarrot() ? " (C)" : "    ");
		    } else if (e != nullptr) {
				cout << "    " << e->getId() << "    ";
			} else {
				cout << "    -    ";
			}
		}
		
		cout << endl;
	}	
}


void PlanetX::printBorder()
{
	for (int i = 0; i < PLANETX_SIZE; ++i)
		cout << "---------";
	
	cout << endl;
}


void PlanetX::printEntities()
{
	for(unsigned i = 0; i < entities.size(); ++i)
		cout << entities[i]->toString()
			 << ": ("
			 << entities[i]->getX()
			 << ", "
			 << entities[i]->getY()
			 << ")"
			 << endl;
	
	for(unsigned i = 0; i < racers.size(); ++i)
		cout << racers[i]->toString()
			 << ": ("
			 << racers[i]->getX()
			 << ", "
			 << racers[i]->getY()
			 << ")"
			 << endl;
}
