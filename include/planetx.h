#ifndef PLANETX_H
#define PLANETX_H


class PlanetX
{
private:
  
public:
	PlanetX();
	~PlanetX();
	

	bool isWon();
	int roundCount();

	// Create racers and entities on PlanetX
	void create();
	
	// Step the race on planetx by one round
	void step();
	
private:
	// Private variables
    mutex planetXMutex;
	thread racerThreads[RACER_COUNT];
    
	Racer racers[RACER_COUNT];
    vector<Entity> entities;
	
	bool m_isWon;
	int m_roundCount;
	
	
	// Private methods
    void randomizeAllEntities(); // randomize racers, carrots, and mountain
    void randomizeEntity(Entity*); // randomize specific entitiy
    
    // Racer's thread routine
	void race(Racer* racer);
    void randomlyMoveRacer(Racer*);
    
    
    // Racer Marvin's thread routine.
    void raceMarvin();
    void randomlyMoveMarvin();

    
    // Helpers for entities and racers
    Entity* getEntityAt(int, int);
    void removeEntity(Entity*);    
    Racer* getRacerAt(int, int);
    void removeRacer(Racer*);

    // Printing
	void printPlanetX();
    void printRacerPositions();
}


#endif /* PLANETX_H */
