#ifndef RACER_H
#define RACER_H


class Racer 
{ 
private:
    string mId;
    bool hasCarrot;


public:
    Racer(string id)
      : mId(id), hasCarrot(false)
      {}
      
    string getId() { return mId; }
    void setId(string newId) { mId = newId; }
};

#endif /* RACER_H */
