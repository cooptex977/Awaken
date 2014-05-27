#pragma once
#include "Main.h"
#include "GameObjects.h"

class Game
{
public:
	void Run();
	void Init();
	void MainLoop();
	void Update();

	int SCREEN_HEIGHT, SCREEN_WIDTH;
	std::vector<Enemy*> enemylist;
	sf::Texture bgtexture;
	sf::Sprite bg;
	std::vector<Tile*> tiles;
	sf::Font font;
	Player* player;
	sf::View view;
	sf::Clock clock;
	float lastTime;
	sf::RenderWindow window; 
	sf::Vector2f viewpos;
};