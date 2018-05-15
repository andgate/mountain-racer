#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "api.h"

API::API()
	: isWon(false)
{}

API::~API() {}

void API::run()
{
	create();
    
    while(!isWon) {
      bunny = thread( [this] { this->race(); } );
	  taz = thread( [this] { this->race(); } );
	  tweety = thread( [this] { this->race(); } );
      marvin = thread( [this] { this->race(); } );
      
      bunny.join();
      taz.join();
      tweety.join();
      marvin.join();
      
      printMountain();
    }
}

void API::create()
{
	Random::create();
}


void API::race()
{
	this->mountainMutex.lock();
    
    // do stuff
    
    this->mountainMutex.unlock();
}


void API::printMountain()
{
}
