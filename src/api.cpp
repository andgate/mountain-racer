#include "api.h"
#include "planetx.h"

#include <iostream>


API::API()
	: planetX(PlanetX())
{}

API::~API()
{}


void API::run()
{
	planetX.create();
	
	int roundCount = 1;
	
    while(!planetX.isWon())
	{
		planetX.step();
    }
    
    cout << "Game lasted " << planetX.roundCount() << " rounds." << endl;
}
