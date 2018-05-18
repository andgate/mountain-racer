#include "api.h"
#include "planetx.h"

#include <iostream>


API::API()
	: planetX()
{}

API::~API()
{}


void API::run()
{
	planetX.create();
    planetX.printEntities();
	
    while(!planetX.isWon())
	{
		planetX.step();
    }
    
    cout << "Game lasted " << planetX.roundCount() << " rounds." << endl;
}
