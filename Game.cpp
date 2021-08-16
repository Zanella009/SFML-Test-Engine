#include "Game.h"
#include <iostream>

void Game::Input()
{
	if (gs == GameStates::MAINMENU) {


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			gs = GameStates::GAME;
		}


	}else if (gs == GameStates::GAME){

		//Entradas do Teclado
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !right) {
			movSnake = sf::Vector2f(-(same), 0);
			left = true;
			up = false;
			down = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !up) {
			movSnake = sf::Vector2f(0, same);
			left = false;
			right = false;
			down = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !left) {
			movSnake = sf::Vector2f(same, 0);
			right = true;
			up = false;
			down = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !down) {
			movSnake = sf::Vector2f(0, -(same));
			left = false;
			right = false;
			up = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			gs = GameStates::MAINMENU;
		}
		
		//Entradas do Mouse



	}else if (gs == GameStates::GAMEOVER) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			gs = GameStates::GAME;
		}

	}
}
void Game::Update()
{

	if (gs == GameStates::MAINMENU) {



	}else if (gs == GameStates::GAME) {
		//Apple infos
		apple.setFillColor(sf::Color::Red);
		apple.setSize(sf::Vector2f(same * 2, same * 2));

		//Demonstração de posição de Snake e Apple
		std::cout << "Head X e Y: " << player.head.getPosition().x << " " << player.head.getPosition().y << std::endl;
		std::cout << "Apple X e Y : " << apple.getPosition().x << " " << apple.getPosition().y << std::endl;
		//*/

		//Checa a colisão da Snake e a Maçã e aumenta o tamanho em 1
		if (player.head.getPosition().x == apple.getPosition().x && player.head.getPosition().y == apple.getPosition().y ||
			player.head.getPosition().x == apple.getPosition().x + same && player.head.getPosition().y == apple.getPosition().y + same) {
			std::cout << "Colidiu" << std::endl;
			player.applesAte++;
			player.tamanho++;
			player.pontuacao++;
			std::cout << player.applesAte;
			if (player.applesAte >= 10) {
				vidas++;
				player.applesAte = 0;
				player.tamanho += 5;
			}
			//Nova posição da maçã após ser comida
			apple.setPosition((int)rand() % width / same * same, (int)rand() % height / same * same);
		}

		if (apple.getPosition().y < 30) {
			apple.setPosition((int)rand() % width / same * same, (int)rand() % height / same * same);
		}

		//Variáveis atualizadas do corpo da snake
		for (int i = 0; i < player.tamanho; i++) {
			player.head.setSize(sf::Vector2f(same, same));
			player.body[i].setSize(sf::Vector2f(same, same));
			player.body[i].setFillColor(sf::Color::Green);
		}

		//Colide com a borda
		if (player.head.getPosition().x > width) {
			player.head.setPosition(sf::Vector2f(0, player.head.getPosition().y));
		}
		else if (player.head.getPosition().x <= 0) {
			player.head.setPosition(sf::Vector2f(width, player.head.getPosition().y));
		}
		else if (player.head.getPosition().y > height) {
			player.head.setPosition(sf::Vector2f(player.head.getPosition().x, 30));
		}
		else if (player.head.getPosition().y <= gameBackGround.getSize().y) {
			player.head.setPosition(sf::Vector2f(player.head.getPosition().x, height-5));
		}
		//Faz o rabo seguir a cabeça e checa colisão com o corpo
		for (int i = player.tamanho; i > 0; i--) {
			player.body[0].setPosition(player.head.getPosition());
			player.body[i].setPosition(player.body[i - 1].getPosition());

			//Colide com o corpo e Corta parte do corpo fora
			if (player.head.getPosition() == player.body[i + 1].getPosition()) {
				std::cout << "Colisao do corpo" << std::endl;
				int numero = i - player.tamanho;
				player.tamanho += numero + 1;

				vidas--;

				if (vidas <= 0) {
					player.tamanho = 5;
					player.pontuacao = 0;
					vidas = 3;
					gs = GameStates::GAMEOVER;

				}
				if (player.tamanho < 5) {
					player.tamanho = 5;
				}
			}
		}
		//Movimenta o player
		player.head.move(movSnake);


	}else if (gs == GameStates::GAMEOVER) {



	}
}
void Game::Render()
{
	if (gs == GameStates::MAINMENU) {
		win.clear();

		//Main Menu
		MainMenu.setPosition(0, 0);
		MainMenu.setSize(sf::Vector2f(width, height));
		MainMenu.setTexture(&MainMenuIMG);
		win.draw(MainMenu);


		win.display();
	}
	else if (gs == GameStates::GAME) {
		//Início do Render
		win.clear();

		//Variáveis do Texto de Pontuação
		txt.setPosition(sf::Vector2f(0, 0));
		txt.setCharacterSize(20);
		txt.setString("Pontuação: " + std::to_string(player.pontuacao) +
			"    " + "Vidas: " + std::to_string(vidas));
		txt.setFillColor(sf::Color::Red);
		txt.setStyle(sf::Text::Underlined);
		txt.setFont(font);

		//BackGroundGame variavéis
		gameBackGround.setSize(sf::Vector2f(width, 25));
		gameBackGround.setFillColor(sf::Color::Color(74,65,210,255));
		gameBackGround.setPosition(sf::Vector2f(0, 0));
		
		//Desenha na tela
		win.draw(gameBackGround);
		win.draw(player.head);
		for (int i = 0; i < player.tamanho; i++) {
			win.draw(player.body[i]);
		}
		win.draw(apple);
		win.draw(txt);
		

		//Fim do Render
		win.display();
	}else if (gs == GameStates::GAMEOVER) {
		win.clear();

		//Game Over
		GameOver.setPosition(0, 0);
		GameOver.setSize(sf::Vector2f(width, height));
		GameOver.setTexture(&GameOverIMG);
		win.draw(GameOver);

		win.display();
	}
}


Game::Game(int width, int height, const char* title)
{
	//Inicializa a Janela com variáveis do construtor
	this->width = width;
	this->height = height;
	win.create(sf::VideoMode(this->width, this->height), title, sf::Style::Close | sf::Style::Titlebar);
	win.setFramerateLimit(30);
	movSnake = sf::Vector2f(0, same);
	apple.setPosition(10,10);
	font.loadFromFile("assets/arial.ttf");
	MainMenuIMG.loadFromFile("assets/Snake.png");
	GameOverIMG.loadFromFile("assets/game-over.png");
	player.head.setPosition(apple.getPosition());
	while (win.isOpen()) {
		while (win.pollEvent(ev)) {
			//Entradas para Controle de Janela
			switch (ev.type) 
			{
				case sf::Event::Closed:
				win.close();
				break;
			}
		}
		Input();
		Update();
		Render();
	}
}
Game::~Game()
{

}
