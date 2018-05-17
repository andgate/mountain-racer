#ifndef RACER_H
#define RACER_H

#include <string>
#include "position.h"
#include "entity.h"

class Racer : public Entity
{ 
private:
    bool m_hasCarrot;
	bool m_isAlive;

public:
	Racer()
	  : Entity("")
	  , m_hasCarrot(false)
	  , m_isAlive(true)
	{}
	
    Racer(string id)
	  : Entity(id)
      , m_hasCarrot(false)
	  , m_isAlive(true)
    {}
    
    ~Racer() {}
    
    void create() {
		Entity::create();
    }
      
    void setHasCarrot(bool hasCarrot) { m_hasCarrot = hasCarrot; }
    bool hasCarrot() { return m_hasCarrot; }
    
    void setIsAlive(bool isAlive) { m_isAlive = isAlive; }
    bool isAlive() { return m_isAlive; }
};

#endif /* RACER_H */
