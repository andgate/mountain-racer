#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "random_position.h"
#include "constants.h"

class Entity : public RandomPosition
{
private:
    string m_name;
	string m_id;
    vector<Position> m_history;
	
public:
	Entity(string name, string id)
		: RandomPosition(-1, -1)
		, m_name(name)
        , m_id(id)
        , m_history()
	{}
	
	Entity(string name, string id, Position pos)
		: RandomPosition(pos)
		, m_name(name)
        , m_id(id)
        , m_history()
	{}
	
	virtual ~Entity() 
    {}
	
    void create() {
		Random::create();
    }
    
    string getName() { return m_name; } 
	string getId() { return m_id; }
	string draw() { return m_id; }
	
	string toString() { return (m_name + " (" + m_id + ")"); }
    
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
