/**
 * Authors:     Gabriel Anderson,
 *              Matthew Harker
 * Assignment:  Project 2, Mountain Racer
 * Class:       CS380
 */

#include "api.h"
#include <SFML/Graphics.hpp>

/**
 * @brief The main file which runs api.h
 * 
 * @return int 
 */
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    API api;
    api.run();
    return 0;
}
