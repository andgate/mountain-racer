#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "api.h"
#include "racer.h"

API::API()
	: isWon(false)
{}

API::~API() {}

void API::run()
{
	create();
    
    Racer* racerBunny  = new Racer("B");
    Racer* racerTaz    = new Racer("D");
    Racer* racerTweety = new Racer("T");
    Racer* racerMarvin = new Racer("M");
    
    while(!isWon) {
      bunny  = thread( [this, racerBunny ] { this->race(racerBunny ); } );
	  taz    = thread( [this, racerTaz   ] { this->race(racerTaz   ); } );
	  tweety = thread( [this, racerTweety] { this->race(racerTweety); } );
      marvin = thread( [this, racerMarvin] { this->race(racerMarvin); } );
      
      bunny.join();
      taz.join();
      tweety.join();
      marvin.join();
    }
    
    delete racerBunny;
    delete racerTaz;
    delete racerTweety;
    delete racerMarvin;
}

void API::create()
{
	Random::create();
}


void API::race(Racer* racer)
{
	this->mountainMutex.lock();
    
    // racer stuff
    cout << racer->getId() << endl;
    
    this->mountainMutex.unlock();
}


void API::printMountain()
{
}
