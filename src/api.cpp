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
    planetX.printBorder();
	
    while(!planetX.isWon())
	{
		planetX.step();
    }

	cout << planetX.getWinner() << " has won!" << endl;
}
