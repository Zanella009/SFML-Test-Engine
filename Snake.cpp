#include "Snake.h"
Snake::Snake()
{
	
	head.setSize(sf::Vector2f(5, 5));
	body->setSize(sf::Vector2f(5, 5));
	body->setFillColor(sf::Color::Green);

}

Snake::~Snake()
{


}
