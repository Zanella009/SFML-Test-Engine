#pragma once

#include <SFML/Graphics.hpp>

class Snake
{
private:
	
	

public:
	Snake();
	~Snake();
	sf::RectangleShape head;
	int tamanho = 1;
	int pontuacao = 0;
	int applesAte = 0;
	sf::RectangleShape body[500];

	
};

