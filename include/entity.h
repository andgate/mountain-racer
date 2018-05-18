#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "random_position.h"
#include "constants.h"

class Entity : public RandomPosition
{
private:
	string m_id;
    vector<Position> m_history;
	
public:
	Entity(string id)
		: RandomPosition(-1, -1)
		, m_id(id)
        , m_history()
	{}
	
	Entity(string id, Position pos)
		: RandomPosition(pos)
		, m_id(id)
        , m_history()
	{}
	
	virtual ~Entity() 
    {}
	
    void create() {
		Random::create();
    }
    
    
	string getId() { return m_id; }
    void setId(string newId) { m_id = newId; }
    
    
    void setPos(int newX, int newY) {
        m_history.push_back(Position(getX(), getY()));
        Position::setPos(newX, newY);
    }
    
    void setPos(Position newPos) {
        m_history.push_back(Position(newPos));
        Position::setPos(newPos);
    }
    
    void undoMove() {
      Position::setPos(m_history.back());
      m_history.pop_back();
    }
};

#endif /* ENTITY_H */
