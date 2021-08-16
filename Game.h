#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Snake.h"


enum class GameStates {MAINMENU, GAME, GAMEOVER};
class Game
{
private:

	//Varíaveis do Jogo
	sf::RectangleShape gameBackGround;
	Snake player;
	sf::RectangleShape MainMenu;
	sf::Texture MainMenuIMG;
	sf::RectangleShape GameOver;
	sf::Texture GameOverIMG;
	sf::Vector2f movSnake;
	sf::RectangleShape apple;
	bool right = true, left = false, up = false, down = false;
	int vidas = 4;
	int same = 5;



	//Variáveis da Game Engine
	sf::RenderWindow win;
	sf::Event ev;
	sf::Text txt;
	sf::Font font;
	sf::String pontos;
	GameStates gs = GameStates::MAINMENU;
	int width, height;
	

	//Métodos da Game Engine
	void Update();
	void Input();
	void Render();

public:
	Game(int width, int height, const char* title);
	~Game();
};
#endif