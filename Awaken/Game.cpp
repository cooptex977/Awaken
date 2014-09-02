#include "Main.h"
#include "GameObjects.h"
#include "HandleInput.h"
#include "Game.h"

void Game::Run()
{
	Init();
	MainLoop();
}

void Game::MainLoop()
{
	//main game loop
	while (window.isOpen())
	{
		sf::Event event;
		//event listening
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		khandle(player); //handle keypress
		
		Update();

		viewpos = sf::Vector2f(player->sprite.getPosition().x + 10 - (800 / 2), player->sprite.getPosition().y + 10 - (600 / 2));

		if (viewpos.x < 0)
			viewpos.x = 0;
		if (viewpos.y < 0)
			viewpos.y = 0;

		view.reset(sf::FloatRect(viewpos.x, viewpos.y, 800, 600));

		window.clear(sf::Color::White); //clear the window
		window.setView(view);
		window.draw(bg);
		for each (Tile* tile in tiles)
		{
			window.draw(tile->sprite);
		}
		window.draw(player->getCurrentSprite()); //draw to the back buffer
		window.display(); //display the back buffer
	}
}

void Game::Init()
{
	window.create(sf::VideoMode(800, 600), "Awaken", sf::Style::Titlebar | sf::Style::Close);
	SCREEN_HEIGHT = window.getSize().y;
	SCREEN_WIDTH = window.getSize().x;
	//set fps limit to 60
	window.setFramerateLimit(60);
	//enable vsync
	window.setVerticalSyncEnabled(true);

	//make a view
	view.reset(sf::FloatRect(0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	float lastTime = 0;

	player = new Player(sf::Vector2f((float)((SCREEN_WIDTH / 2) - 32), (float)((SCREEN_HEIGHT / 2) - 32)));

	if (!font.loadFromFile("assets/fonts/consola.ttf"))
		MessageBox(0, L"Error: failed to load asset", L"Error", MB_ABORTRETRYIGNORE);

	if (!player->texture.loadFromFile("assets/images/player.png"))
		MessageBox(0, L"Error: failed to load asset", L"Error", MB_ABORTRETRYIGNORE);
	else
		player->sprite.setTexture(player->texture);
	if (!bgtexture.loadFromFile("assets/images/bg.png"))
		MessageBox(0, L"Error: failed to load asset", L"Error", MB_ABORTRETRYIGNORE);
	else
		bg.setTexture(bgtexture);

	tiles.push_back(new Tile(sf::Vector2f((SCREEN_WIDTH / 2) - 32, (SCREEN_HEIGHT / 2) + 32)));
	tiles.push_back(new Tile(sf::Vector2f((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 32)));
	tiles.push_back(new Tile(sf::Vector2f((SCREEN_WIDTH / 2) + 32, SCREEN_HEIGHT / 2)));
	tiles.push_back(new Tile(sf::Vector2f((SCREEN_WIDTH / 2) - 64, SCREEN_HEIGHT / 2)));
	tiles.push_back(new Tile(sf::Vector2f((SCREEN_WIDTH / 2) - 64, (SCREEN_HEIGHT / 2) - 128)));
	int count = 0;
}

void Game::Update()
{
	if (player->vel.y > 100)
		player->vel.y = 100;
	if (!player->isTouchingGround)
		player->vel.y += player->gravity;
	if (player->vel != sf::Vector2f(0, 0))
		player->sprite.move(player->vel);
	player->isTouchingGround = false;
	for each (Tile* tile in tiles)
	{
		if (tile->sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
		{
			player->isTouchingGround = true;
			//top
			if (player->sprite.getPosition().y < tile->sprite.getPosition().y)
				player->sprite.setPosition(player->sprite.getPosition().x, tile->sprite.getPosition().y - tile->sprite.getGlobalBounds().height);
			//left
			else if (player->sprite.getPosition().x + player->sprite.getGlobalBounds().width - 8 > tile->sprite.getPosition().x)
				player->sprite.setPosition(tile->sprite.getPosition().x - (tile->sprite.getGlobalBounds().width - 8), player->sprite.getPosition().y);
			//right
			else
				player->sprite.setPosition(tile->sprite.getPosition().x - abs(tile->sprite.getPosition().x - player->sprite.getPosition().x), player->sprite.getPosition().y);
		}
	}
}