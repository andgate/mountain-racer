#ifndef RACER_H
#define RACER_H

#include <string>
#include "position.h"
#include "entity.h"

class Racer : public Entity
{ 
private:
    bool m_hasCarrot;
    bool m_onMountain;

public:
	Racer()
	  : Entity("")
	  , m_hasCarrot(false)
	  , m_onMountain(false)
	{}
	
    Racer(string id)
	  : Entity(id)
      , m_hasCarrot(false)
      , m_onMountain(false)
    {}
    
    ~Racer() {}
    
    void create() {
		Entity::create();
    }
      
    void setHasCarrot(bool hasCarrot) { m_hasCarrot = hasCarrot; }
    bool hasCarrot() { return m_hasCarrot; }
};

#endif /* RACER_H */
