#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "random_position.h"
#include "constants.h"

class Entity : protected RandomPosition
{
private:
	string m_id;
	
public:
	Entity(string id)
		: RandomPosition(-1, -1)
		, m_id(id)
	{}
	
	Entity(string id, Position pos)
		: RandomPosition(pos)
		, m_id(id)
	{}
	
	~Entity() {}
	
    void create() {
		Random::create();
    }
    
    
	string getId() { return m_id; }
    void setId(string newId) { m_id = newId; }

	/*
	void randomlyMove()
	{
		Position nextPos;
		do {
			nextPos = Position::fromDirection(getX(), getY());
		} while (nextPos.inBounds(0, PLANETX_SIZE-1));
		
		setPos(nextPos.getX(), nextPos.getY());
	}*/
};

#endif /* ENTITY_H */
