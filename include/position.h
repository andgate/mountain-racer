#ifndef POSITION_H
#define POSITION_H


class Position {
private:
    int m_x;
    int m_y;
    
public:
    Position()
      : m_x(0), m_y(0)
    {}
    
    Position(const Position& other)
      : m_x(other.m_x), m_y(other.m_y)
    {}
  
    Position(int x, int y)
      : m_x(x), m_y(y)
    {}
      
    ~Position() {}
  
  
    void setPos(int newX, int newY)
      { m_x = newX; m_y = newY; }
    
    void setPos(Position newPos)
      { m_x = newPos.getY(); m_y = newPos.getX(); }
    
    void setX(int newX) { m_x = newX; }
    void setY(int newY) { m_y = newY; }
    int getX() { return m_x; }
    int getY() { return m_y; }
    
    
    void add(Position other)
		{
			m_x += other.getX();
			m_y += other.getY();
		}
    
    bool at(int atX, int atY) {
      return (m_x == atX) && (m_y == atY);
    
    
    bool inBounds(int min, int max)
		{
				return (0 <= m_x) && (m_x <= max) && (0 <= m_y) && (m_y <= max);
		}
    
    
		static Position fromDirection(int x, int y, int direction)
    {
			switch(direction)
			{
				case 0:
					x += 0; y += -1; break; // Move up
				case 1:
					x += 0; y += 1; break; // Move down
				case 2:
					x += -1; y += 0; break; // Move left
				case 3:
					x += 1; y += 0; break; // Move right
				default:
					x += 0; y += 0; break;
			}
		
			return Position(x, y);
    }
};

#endif /* POSITION_H */
