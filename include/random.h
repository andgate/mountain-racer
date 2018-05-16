#ifndef RANDOM_H
#define RANDOM_H

#include <random>

using namespace std;

/**
 * @brief Class for random number generation.
 *
 *  This class is meant to be inherited. Specifially, the
 *  create method should be overriden. This class allows
 *  its children to internally generate random numbers.
 *  In addition, this class will not conflict with other
 *  random number generators that are in use.
 */
class Random
{
private:
    typedef mt19937 RNG; // Use mersenne twister as internal rng
    RNG m_rng;
    
public:
    /**
	 * @brief Default constructor for Random.
	 */
    Random()
    : m_rng() {}
    
    /**
	 * @brief Default destructor for Random.
	 */
    ~Random() {}
 
protected:
    /**
    * @brief Create the random number generator.
    * 
    *  This method needs to be overriden.
    */
    virtual void create()
    {
        m_rng.seed(random_device()());
    }
    
    /**
    * @brief Randomly returns a value from min to max
    * 
    * @param min minimal value that can be generated
    * @param max maximum value that can be generated
    * @return some random integer between 0 and max
    */
    int randomInt(int min, int max)
    {
        uniform_int_distribution<RNG::result_type> dist(min, max);
        return dist(m_rng);
    }

};

#endif /* RANDOM_H */
