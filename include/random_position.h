#ifndef RANDOM_POSITION_H
#define RANDOM_POSITION_H

#include "random.h"
#include "position.h"


class RandomPosition : protected Random, public Position
{
public:
	RandomPosition(const Position& other) 
		: Random()
		, Position(pos)
	{}
	
	
	RandomPosition(int posX, int posY) 
		: Random()
		, Position(posX, posY)
	{}
	
	RandomPosition() 
		: Random()
		, Position()
	{}
	
	
	void create()
	{
		Random::create();
	}
	 

    Position randomPosition(int min, int max)
	{
		return Position( randomInt(min, max)
		               , randomInt(min, max)
					   );
	}
	
	Position randomPosition(Position min, Position max)
	{
		return Position( randomInt(min.getX(), max.getX())
		               , randomInt(min.getY(), max.getY())
					   );
	}
	
	
	Position randomDirection()
	{
		int direction = randomInt(0, 3);
		Position pos = Position::fromDirection(direction);
		
		return Position(x, y);
	}
}



#endif /* RANDOM_POSITION_H */
