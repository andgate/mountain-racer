#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "random.h"
#include "position.h"
#include "constants.h"

class Entity : protected Random, public Position
{
private:
	string m_id;
	
public:
	Entity(string id)
		: Position(-1, -1)
		, m_id(id)
	{}
	
	Entity(string id, Position pos)
		: Position(pos)
		, m_id(id)
	{}
	
	~Entity() {}
	
    void create() {
		Random::create();
    }
    
    
	string getId() { return m_id; }
    void setId(string newId) { m_id = newId; }
    
    void randomPosition(int min, int max)
	{
		setPos(randomInt(min, max), randomInt(min, max));
	}
	
	void randomlyMove(int max)
	{
		int dx, dy;
		int direction = randomInt(0, 3);
		switch(direction)
		{
			case 0:
				dx = 0; dy = -1; break; // Move up
			case 1:
				dx = 0; dy = 1; break; // Move down
			case 2:
				dx = -1; dy = 0; break; // Move left
			case 3:
				dx = 1; dy = 0; break; // Move right
			default:
				dx = 0; dy = 0; break;
		}
		
		setPos( dx < 0 ? (dx + getX() + max) % max
				       : (dx + getX()      ) % max
			  , dy < 0 ? (dy + getY() + max) % max
					   : (dy + getY()      ) % max
			  );
	}
};

#endif /* ENTITY_H */
