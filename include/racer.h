#ifndef RACER_H
#define RACER_H

#include "position.h"

class Racer 
{ 
private:
    string mId;
    Position pos;

public:
    Racer(string id)
      : mId(id)
      , pos(Position(0, 0))
      {}
      
      
    string getId() { return mId; }
    void setId(string newId) { mId = newId; }
    Position* getPos() { return &pos; }
};

#endif /* RACER_H */
