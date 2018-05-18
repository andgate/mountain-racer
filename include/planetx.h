#ifndef PLANETX_H
#define PLANETX_H

#include "constants.h"
#include "entity.h"
#include "racer.h"
#include "position.h"

#include <memory>
#include <mutex>
#include <thread>
#include <vector>


using namespace std;


class PlanetX
{
private:
  
public:
	PlanetX();
	~PlanetX();
	

    // check the status of the race
	bool isWon();
	int roundCount();

	// Create racers and entities on PlanetX
	void create();
	
	// Step the race on planetx by one round
	void step();
    
    // Printing output
	void printPlanetX();
    void printEntities();
    
private:
	// Private variables
    mutex planetXMutex;
	thread racerThreads[RACER_COUNT];
    
	vector<shared_ptr<Racer>> racers;
    vector<shared_ptr<Entity>> entities;
	
	bool m_isWon;
	int m_roundCount;
	
	
	// Private methods
    void randomizeAllEntities(); // randomize racers, carrots, and mountain
    void randomizeEntity(shared_ptr<Entity>); // randomize specific entitiy
    
    // Racer's thread routine
	void race(shared_ptr<Racer>);
    void randomlyMoveRacer(shared_ptr<Racer>);
    void randomlyMoveMountain();

    // Helpers for entities and racers
    shared_ptr<Entity> getAnyEntityAt(Position);
    shared_ptr<Entity> getAnyEntityAt(int, int);
    
    // Helpers for entities
    shared_ptr<Entity> getEntityAt(Position);
    shared_ptr<Entity> getEntityAt(int, int);
    void removeEntity(shared_ptr<Entity>);    
    
    // Helpers for racers
    shared_ptr<Racer> getRacerAt(Position);
    shared_ptr<Racer> getRacerAt(int, int);
    void removeRacer(shared_ptr<Racer>);
    
    shared_ptr<Entity> collidesAnyEntity(shared_ptr<Entity>);
    shared_ptr<Entity> collidesEntity(shared_ptr<Entity>);
    shared_ptr<Racer> collidesRacer(shared_ptr<Entity>);
};

#endif /* PLANETX_H */
