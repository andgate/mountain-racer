#ifndef POSITION_H
#define POSITION_H


class Position {
private:
    int m_x;
    int m_y;
  
    
public:
    Position(int x, int y)
      : m_x(x), m_y(y)
      {}
    ~Position() {}
  
    void move(int moveX, int moveY)
      { m_x += moveX; m_y += moveY; }
    
    void setPos(int newX, int newY)
      { m_x = newX; m_y = newY; }
    
    
    void setX(int newX) { m_x = newX; }
    void setY(int newY) { m_y = newY; }
    int getX() { return m_x; }
    int getY() { return m_y; }
    
    bool at(int atX, int atY) {
      return (m_x == atX) && (m_x == atY);
    }
};

#endif /* POSITION_H */
